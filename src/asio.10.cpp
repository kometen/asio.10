#include <iostream>
#include "tcp_server.hpp"

using namespace std;

int main() {
	cout << "asio.10 Blåbærsyltetøj" << endl; // prints Blåbærsyltetøj
	try {
        asio::io_service io_service;
        tcp_server server{io_service};
        io_service.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
	return 0;
}
