#include <iostream>
#include "async.h"
#include <unistd.h>
#include <chrono>


int main() {

   auto h1 = async::connect(1);
   auto h2 = async::connect(3);
   
   async::receive(h1, "\ncmd2\ncmd3\ncmd4\ncmd5\ncmd6\n{\ncmda\n", 33);
   async::receive(h2, "cmdb\ncmdc\ncmdd\n}\ncmd89\n", 23);

   // sleep is needed for tests purposes, as we do disconnect immediately, respective context can be not serviced as context is gone
   // it's FAD, connect& disconnect do not share same queue with receive  
   usleep(10000);

   async::disconnect(h1);

   return 0;

} 
