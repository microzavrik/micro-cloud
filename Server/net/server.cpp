#include "server.hpp"

namespace net
{
    server::server(boost::asio::io_context& ios, short port, db::users_db_manager& db)
        : acceptor_(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
          db_(db)
    {
        BOOST_LOG_TRIVIAL(info) << "Server started";
        do_accept();
    }

    void server::do_accept() {
        acceptor_.async_accept(
            [this](const boost::system::error_code& ec, boost::asio::ip::tcp::socket socket) {
                if (!ec) {
                    BOOST_LOG_TRIVIAL(info) << "New user connected";
                    std::make_shared<net::session>(std::move(socket), db_)->start();
                }

                do_accept();
            });
    }
}