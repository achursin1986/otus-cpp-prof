#include <database.hpp>
#include <iostream>
#include <threadpool.hpp>
#include <boost/asio.hpp>
#include "server.hpp"

int main(int argc, char* argv[]) {

        if ( argc != 2 ) {
                  std::cerr << "Usage: join_server <port>" << std::endl;
        return 1;
        }
	try {
		my::Database* db = my::Database::GetDatabase("Database");
                boost::asio::io_context io_context;
                tcp_server server(io_context,std::atoi(argv[1]));
                io_context.run();                

	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
