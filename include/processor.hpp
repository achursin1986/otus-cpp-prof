#pragma once 

//#include <mutex>
//#include <condition_variable>
//#include <deque>
#include <vector>
#include <atomic>
#include <array>
#include <exception>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <memory>
#include <cstring>

#include"async.h"
#include"data.hpp"
#include"parser.hpp"
#include"threadpool.hpp"







namespace my {

struct Combi {
      Combi(std::size_t N): Data(data()), Parser(parser("{","}","cmd", N ,&Data)) { }
      data Data;
      parser Parser;
      // ref to pools 
};


static std::unordered_map<void * ,std::shared_ptr<Combi>> contexts;
static std::mutex mtx; // global mutex




struct Receive {
      Receive(): handle(nullptr),data(nullptr),size(0) {}
     
      Receive& operator=(const Receive& other) {
             handle = other.handle;
             size = other.size;
             data = other.data;
             return *this;
      }
      Receive(async::handle_t handle_, std::shared_ptr<char[]>&&data_, std::size_t size_): handle(handle_),data(std::move(data_)),size(size_){};
      async::handle_t handle; 
      std::shared_ptr<char[]> data;
      //std::unique_ptr<char[]> data; 
      std::size_t size;
};



// non-blocking queue 

template <typename T,size_t N>
class lfq {
       public:
        lfq()  {
              assert(size_.is_lock_free());
        }

        auto size() const {  return size_.load(); }


       auto push(const T& t) {
             if ( size_.load() >= N) {
                 throw std::overflow_error("Queue is full");
             }
             buffer_[write_pos_] = t;  
             write_pos_ = (write_pos_ + 1) % N;
             size_.fetch_add(1);
       }

       auto& front() const {
             if ( size_.load() == 0 ) {
                   throw std::underflow_error("Queue is empty");
             }
             return buffer_[read_pos_];
             }
       
       auto pop(){ 
            if ( size_.load() == 0 ) {
                   throw std::underflow_error("Queue is empty");
             }
            read_pos_ = ( read_pos_ + 1) % N;
            size_.fetch_sub(1);
       }
      private:
         std::array<T, N> buffer_;
         std::atomic<size_t> size_{0};
         size_t read_pos_{0}, write_pos_{0};
};



template <typename T>
class scheduler{ 
   public:
    scheduler(){
          running_ = true;
          th_ = std::thread{&scheduler::process, this};
          //std::cout << "Started" << std::endl;     

    } 
    ~scheduler() {
           //std::cout << "Stopping... " << std::endl;
           { std::unique_lock<std::mutex> lock(mtx_);
           running_ = false; }
           cv_.notify_one();
           th_.join(); 
    } 
   
    void process();
    void schedule(const T& i);

    
    private:

    void queue_walk(); 
    

    lfq<T,10> queue_;
    std::thread th_;
    std::condition_variable cv_; 
    std::mutex mtx_;
    bool running_;

};


template <typename T>
void scheduler<T>::schedule(const T& i) {
        std::unique_lock<std::mutex> lock(mtx_); // here could be different lock only for entrance 
        queue_.push(i);
        cv_.notify_one();     
}

template <typename T>
void scheduler<T>::queue_walk() {
         while  ( queue_.size() ) {
                     // taking global mtx
                     std::lock_guard<std::mutex> lock(mtx);
                     // look if handle exists
                     if (contexts.find(queue_.front().handle) != contexts.end()) {
                            char* p = queue_.front().data.get();
                            std::string str;
                            // loop to tokenize
                            for ( int i=0; i<queue_.front().size; i++ ) {
                                       if ( p[i] != '\n') { str.append(1,p[i]); }
                                       else { contexts[queue_.front().handle].get()->Parser.check(str); str.clear(); }
                            }
                     }
                     queue_.pop();
          }
}


template <typename T>
void scheduler<T>::process(){
        while(1) {
              std::unique_lock<std::mutex> lock(mtx_);
              cv_.wait(lock, [this](){ return !running_ || queue_.size(); });              
              queue_walk();
              if ( ! running_ ) {    
                     // drain queue on exit  
                    queue_walk();
                    break;
             }          
        }

}


} 

static my::scheduler<struct my::Receive> Scheduler;



