#include <iostream>
#include <exception>
#include <boost/asio.hpp>
#include "server.hpp"
#include "async.h"



int main(int argc, char* argv[]) {

   if ( argc != 3 ) { 
       std::cerr << "Usage: bulk_server <port> <bulk_size>" << std::endl;
       return 1;

   }

  try{
        boost::asio::io_context io_context;
        tcp_server server(io_context,std::atoi(argv[1]),std::atoi(argv[2]));
        io_context.run();
   }
   catch ( std::exception& e) {
      std::cerr << e.what() << std::endl;
   }

  return 0;

}
