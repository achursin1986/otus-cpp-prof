#include "async.h"
#include <mutex>
#include <unordered_map>
#include "processor.hpp"
#include "threadpool.hpp"
#include <cstring>




namespace async {

handle_t connect(std::size_t bulk) {
     
    std::lock_guard<std::mutex> lock(my::mtx);
    //std::shared_ptr<my::Combi> c( new my::Combi(bulk));
    std::unique_ptr<my::Combi> c( new my::Combi(bulk));  
    void * p = c.get();  
    my::contexts[p] = std::move(c);


    return my::contexts[p].get();    
        // return nullptr;
}

void receive(handle_t handle, const char *data, std::size_t size) { 
    //std::shared_ptr<char[]> s (new char[size] );
    std::unique_ptr<char[]> s (new char[size] );
    std::memcpy(s.get(), data ,size);  
    Scheduler.schedule(my::Receive(handle,std::move(s),size));
}



void disconnect(handle_t handle) {
     //walk_and_save(handle);
     std::lock_guard<std::mutex> lock(my::mtx);
     //walk_and_save(handle); 
     my::contexts.erase(handle);

}

}

