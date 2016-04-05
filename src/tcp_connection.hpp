#ifndef TCP_CONNECTION_HPP_
#define TCP_CONNECTION_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <asio.hpp>

using asio::ip::tcp;

class tcp_connection :public boost::enable_shared_from_this<tcp_connection> {
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(asio::io_service&);
    tcp::socket& socket();
    void start();
    virtual ~tcp_connection();

private:
    tcp_connection(asio::io_service&);
    void handle_write(const asio::error_code& /* error */, size_t /* bytes transferrred */);
    tcp::socket socket_;
    tcp::endpoint endpoint_;
    std::string message_;
};

#endif /* TCP_CONNECTION_HPP_ */
