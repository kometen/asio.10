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
    message_ = make_daytime_string();

    asio::async_write(socket_, asio::buffer(message_),
            boost::bind(&tcp_connection::handle_write, shared_from_this(),
                    asio::placeholders::error,
                    asio::placeholders::bytes_transferred));
}

tcp_connection::~tcp_connection() { }

tcp_connection::tcp_connection(asio::io_service& io_service) : socket_{io_service} { }

void tcp_connection::handle_write(const asio::error_code&, size_t) { }
