#include "session.hpp"

#include "packet_valid.hpp"

namespace net
{
    session::session(boost::asio::ip::tcp::socket socket, db::users_db_manager& db) 
        : socket_(std::move(socket)), db_(db)
    {
    }

    void session::start()
    {
        do_read();
    }

    void session::do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](const boost::system::error_code& ec, size_t length)
            {
                if (!ec)
                {
                    std::string message(data_, length);
                    std::cout << message << std::endl;
                    if(net::valid_packet(message)) {
                        BOOST_LOG_TRIVIAL(info) << "Valid packet";
                    }
                    else {
                        BOOST_LOG_TRIVIAL(info) << "Unvalid packet";
                    }

                    do_write(length);
                }
                else if (ec == boost::asio::error::eof)
                {
                    BOOST_LOG_TRIVIAL(info) << "User disconnect";
                }
                else
                {
                    BOOST_LOG_TRIVIAL(error) << "Unkown Error";
                }
        });
    }

     void session::do_write(size_t length)
    {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            [this, self](const boost::system::error_code& ec, size_t /*length*/)
            {
                if (!ec)
                {
                    do_read();
                }
                else
                {
                    // Handle write error
                }
            });
    }
}