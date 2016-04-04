#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_

#include "tcp_connection.hpp"

class tcp_server {
public:
    tcp_server(asio::io_service&);
    virtual ~tcp_server();

private:
    void start_accept();
    void handle_accept(tcp_connection::pointer, const asio::error_code&);
    tcp::acceptor acceptor_;
};

#endif /* TCP_SERVER_HPP_ */
