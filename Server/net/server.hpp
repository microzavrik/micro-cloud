#ifndef SERVER_HPP
#define SERVER_HPP
#define BOOST_LOG_DYN_LINK 1

#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "session.hpp"

namespace net
{
    class server
    {
    public:
        server(boost::asio::io_context& ios, short port, db::users_db_manager& db);
    private:
        void do_accept();
    private:
        boost::asio::ip::tcp::acceptor acceptor_;
        db::users_db_manager& db_;
    };
}

#endif