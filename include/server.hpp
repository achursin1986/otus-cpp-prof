#pragma once
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <memory>
#include <utility>
#include <iostream>
#include <cstdlib>
#include "async.h"

using boost::asio::ip::tcp;
using namespace async;

class tcp_session : public std::enable_shared_from_this<tcp_session> {
    public:
        tcp_session(tcp::socket socket, handle_t handle) : socket_(std::move(socket)), handle_(handle) {}

	void start() {
             do_read();
        }
        ~tcp_session() {
              #ifdef DEBUG  
              std::cout << "Session terminates, port " << std::to_string(socket_.remote_endpoint().port()) << std::endl;
              #endif 
              disconnect(handle_); 

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
                                         receive(handle_, const_cast<char*>(str.c_str()), length); 
                                         data_.consume(length);
                                         do_read();
                                }
                         } );
        }


	tcp::socket socket_;
	boost::asio::streambuf data_;
        handle_t handle_; 
};

class tcp_server {
    public:
	tcp_server(boost::asio::io_context& io_context, short port, int bulk)
	    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), bulk_(bulk) {
		do_accept();
	}

    private:
	void do_accept() {
		acceptor_.async_accept( [this](boost::system::error_code ec, tcp::socket socket) { 

                        if (!ec) {
                             auto handle = async::connect(bulk_);
                             std::make_shared<tcp_session>(std::move(socket), handle)->start();

                        }
                        do_accept();

                 });
	}

	tcp::acceptor acceptor_;
        int bulk_;
};


