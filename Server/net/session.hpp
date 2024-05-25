#ifndef SESSION_HPP
#define SESSION_HPP
#define BOOST_LOG_DYN_LINK 1

#include <iostream>
#include <fstream>

#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>

#include "../database/users_db_manager.hpp"

namespace net
{
    class session : public std::enable_shared_from_this<session>
    {
    public:
        session(boost::asio::ip::tcp::socket socket, db::users_db_manager& db);
        void start();
    private:
        void do_read();
        void do_write(size_t length);
    private:
        boost::asio::ip::tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];

        db::users_db_manager& db_;
    };
}

#endif