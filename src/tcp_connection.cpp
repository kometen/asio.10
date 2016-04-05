#include "tcp_connection.hpp"

std::string make_daytime_string() {
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

tcp_connection::pointer tcp_connection::create(asio::io_service& io_service) {
    return pointer{new tcp_connection{io_service}};
}

tcp::socket& tcp_connection::socket() {
    return socket_;
}

void tcp_connection::start() {
    for (;;) {
        boost::array<char, 256> buf;
        asio::error_code error;

        size_t len = socket_.read_some(asio::buffer(buf), error);

        if (error == asio::error::eof) {
            break;                              // Closed by peer.
        } else if (error) {
            throw asio::system_error(error);    // Something went astray.
        }
//        std::cout.write(buf.data(), len);

        message_ = make_daytime_string();
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: ";
        response += std::to_string(message_.size()) + "\r\nConnection: close\r\n\r\n" + message_;

        asio::async_write(socket_, asio::buffer(response),
                boost::bind(&tcp_connection::handle_write, shared_from_this(),
                        asio::placeholders::error,
                        asio::placeholders::bytes_transferred));
    }
//    std::cout << "Done reading." << std::endl;
/*
    message_ = make_daytime_string();

    asio::async_write(socket_, asio::buffer(message_),
            boost::bind(&tcp_connection::handle_write, shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));*/
}

tcp_connection::~tcp_connection() { }

tcp_connection::tcp_connection(asio::io_service& io_service) : socket_{io_service} { }

void tcp_connection::handle_write(const asio::error_code&, size_t) { }
