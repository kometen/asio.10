#include "tcp_server.hpp"

tcp_server::tcp_server(asio::io_service& io_service) : acceptor_{io_service, tcp::endpoint{tcp::v4(), 2013}} {
    start_accept();
}

tcp_server::~tcp_server() {
}

void tcp_server::start_accept() {
    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());
    acceptor_.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_connection,
                    asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const asio::error_code& error) {
    if (!error) {
        new_connection->start();
    }

    start_accept();
}
