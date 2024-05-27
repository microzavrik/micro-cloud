#include "session.hpp"

#include "packet_valid.hpp"
#include "packet_type_return.hpp"
#include "packet/packet_handler_manager.hpp"
#include "packet_file_info_return.hpp"

#define PUSH_FILE_MARK "push_file"

namespace net
{
    session::session(boost::asio::ip::tcp::socket socket, db::users_db_manager& db) 
        : socket_(std::move(socket)), db_(db) { }

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
                if (!ec) {
                    std::string message(data_, length);
                    BOOST_LOG_TRIVIAL(info) << message;
                    if(net::valid_packet(message)) {
                        BOOST_LOG_TRIVIAL(info) << "Valid packet";
                    }
                    else {
                        BOOST_LOG_TRIVIAL(info) << "Invalid packet";
                        throw std::runtime_error("invalid packet");
                    }

                    if(net::packet_return_type(message) == PUSH_FILE_MARK) {
                        recv_file = true;
                        current_recv_file_info = net::packet_file_info_return(message);
                        BOOST_LOG_TRIVIAL(info) 
                            << current_recv_file_info.file_name << ", " 
                            << current_recv_file_info.file_extension << ", " 
                            << current_recv_file_info.file_size << std::endl;
                    }
                    else {
                        auto [res_bool, text] = net::packet::packet_handler_manager::handle_packet(net::packet_return_type(message), message, db_, socket_);
                        BOOST_LOG_TRIVIAL(info) << "Packet return data: " << "[" << res_bool << "]: " << text;
                        send_message(text);
                    }
                    do_write(length);
                }
                else if (ec == boost::asio::error::eof) {
                    BOOST_LOG_TRIVIAL(info) << "User disconnect";
                }
                else {
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
                if (!ec) {
                    do_read();
                }
                else {
                    // Handle write error
                }
            });
    }

    void session::send_message(const std::string& message)
    {
        auto self(shared_from_this());
        boost::asio::async_write(socket_, boost::asio::buffer(message),
            [&](const boost::system::error_code& ec, size_t /*length*/)
            {
                if(!ec) {
                    BOOST_LOG_TRIVIAL(info) << "Message sent: " << message ;
                }
                else {
                    BOOST_LOG_TRIVIAL(error) << "Error sending message: " << message;
                }
            });
    }
}