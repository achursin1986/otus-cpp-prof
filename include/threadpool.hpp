#pragma once 

#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <iostream>

namespace my {


template <size_t N>
class Thread_pool {
    public:
      Thread_pool();
      ~Thread_pool();
      void Worker();
      void Add_task(const std::function<void()>& job);

    private:
      std::vector<std::thread> threads_;
      std::queue<std::function<void()>> jobs_;
      std::mutex mtx_;
      std::condition_variable cv_;
      bool running_{true};
      
  
};


template <size_t N>
 Thread_pool<N>::Thread_pool() {
      threads_.resize(N);
      for ( int i=0; i < N; i++ ) threads_[i] = std::thread(&Thread_pool<N>::Worker,this);
 }
template <size_t N>
 Thread_pool<N>::~Thread_pool() {
        {
           std::unique_lock<std::mutex> lock(mtx_);
           running_ = false;
        }
        cv_.notify_all();
        for (auto& i : threads_) {
        i.join();
    }
 }
template <size_t N>
void Thread_pool<N>::Worker() {
            while(1) {
                 std::function<void()> job;
                 std::unique_lock<std::mutex> lock(mtx_);
                 cv_.wait(lock, [this]() { return jobs_.size() || !running_;});
                 if  ( jobs_.size() ) {
                         job = jobs_.front();
                         jobs_.pop();
                         lock.unlock();
                         job();  }

             if ( ! running_ ) {
                   break;
             }
          }
}

template <size_t N>
void Thread_pool<N>::Add_task(const std::function<void()>& job) {
          {
               std::unique_lock<std::mutex> lock(mtx_);
               jobs_.push(job);
          }
          cv_.notify_all();

}

static Thread_pool<2> File_writer;
static Thread_pool<1> Console_writer;


}

