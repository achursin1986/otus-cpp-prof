#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <database.hpp>

using boost::asio::ip::tcp;

class tcp_session : public std::enable_shared_from_this<tcp_session> {
    public:
        tcp_session(tcp::socket socket) : socket_(std::move(socket)) {}

        void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/) {}

	void start() {
             do_read();
        }
        ~tcp_session() {
              #ifdef DEBUG  
              std::cout << "Session terminates, port " << std::to_string(socket_.remote_endpoint().port()) << std::endl;
              #endif 

         } 

    private:
        void do_read() {
                        auto self(shared_from_this());
                        socket_.async_read_some(data_.prepare(1500), [this,self](const boost::system::error_code ec, std::size_t length) {
                                if (!ec ) {
                                         data_.commit(length);
                                         #ifdef DEBUG
                                         std::cout << "Received " << length << " bytes "<< "from " << std::to_string(socket_.remote_endpoint().port()) << std::endl;
                                         #endif
                                         std::string str(boost::asio::buffers_begin(data_.data()), boost::asio::buffers_begin(data_.data()) + length);
                                         my::DB_ops.Add_task([str,this](){ 
                                                 std::stringstream ss(str);
                                                 std::string command;
                                                 ss >> command;
                                                 if ( command == "INSERT" ) { 
                                                          std::string table,id,value;
                                                          ss >> table >> id >> value;
                                                          do_write(my::Database::Insert(std::move(table),std::atoi(id.c_str()),std::move(value)));
                                                 }
                                                 else if ( command == "TRUNCATE" ) { 
                                                          std::string table;
                                                          ss >> table;
                                                          do_write(my::Database::Truncate(std::move(table)));
                                                 }       
                                                 else if ( command == "INTERSECTION" ) { 
                                                          do_write(my::Database::Intersection());
                                                 }
                                                 else if ( command == "SYMMETRIC_DIFFERENCE" ) { 
                                                          do_write(my::Database::Symmetric_Difference());   

                                                 }
                                                 else do_write("ERR Entered command is not valid\n");        

                                         }); 
                                         data_.consume(length);
                                         do_read();
                                }
                         } );
        }

        void do_write(std::string reply) {
               auto self(shared_from_this());
               boost::asio::async_write(socket_, boost::asio::buffer(reply), boost::bind(&tcp_session::handle_write, shared_from_this(),boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
        }
	tcp::socket socket_;
	boost::asio::streambuf data_;
};

class tcp_server {
    public:
	tcp_server(boost::asio::io_context& io_context, short port)
	    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
		do_accept();
	}

    private:
	void do_accept() {
		acceptor_.async_accept( [this](boost::system::error_code ec, tcp::socket socket) { 

                        if (!ec) {
                             std::make_shared<tcp_session>(std::move(socket))->start();

                        }
                        do_accept();

                 });
	}

	tcp::acceptor acceptor_;
};


