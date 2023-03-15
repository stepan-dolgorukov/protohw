#include <boost/asio.hpp>
#include <iostream>
#include <string>

std::string
read(boost::asio::ip::tcp::socket& sock) {
    boost::asio::streambuf sbuf{};
    boost::asio::read_until(sock, sbuf, '\n');

    return boost::asio::buffer_cast<const char*>(sbuf.data());
}

void
send(boost::asio::ip::tcp::socket& socket, const std::string& msg) {
    boost::asio::write(socket, boost::asio::buffer(msg));
}

int
main(void) {
    boost::asio::io_service io_serv{};
    boost::asio::ip::tcp::socket socket(io_serv);

    boost::asio::ip::tcp::acceptor accr{
        io_serv, boost::asio::ip::tcp::endpoint{
                     boost::asio::ip::address::from_string("127.0.0.1"), 7777}};

    std::string msg{};

    while (true) {
        boost::asio::ip::tcp::socket sock{io_serv};
        accr.accept(sock);

        std::string msg{read(sock)};
        std::cout << msg << std::endl;

        send(sock, msg);
        sock.close();
    }
}
