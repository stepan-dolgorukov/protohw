#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

class session {
   private:
    boost::asio::ip::tcp::socket sock;
    std::string to_send;

   public:
    static std::shared_ptr<session>
    init(boost::asio::io_service& ioserv) {
        return std::shared_ptr<session>(new session(ioserv));
    }

    boost::asio::ip::tcp::socket&
    socket(void) {
        return sock;
    }

    void
    read(void) {
        boost::asio::streambuf sbuf{};
        boost::asio::read_until(sock, sbuf, '\n');

        to_send = boost::asio::buffer_cast<const char*>(sbuf.data());
    }

    void
    send(void) {
        std::cout << to_send << std::endl;
        boost::asio::write(sock, boost::asio::buffer(to_send));
    }

   protected:
    session(boost::asio::io_service& ioserv) : sock{ioserv} {
    }
};

int
main(void) {
    boost::asio::io_service io_serv{};

    boost::asio::ip::tcp::acceptor accr{
        io_serv, boost::asio::ip::tcp::endpoint{
                     boost::asio::ip::address::from_string("127.0.0.1"), 7777}};

    while (true) {
        auto sess = session::init(io_serv);
        accr.accept(sess->socket());

        sess->read();
        boost::thread(boost::bind(&session::send, sess)).detach();
    }
}
