#ifndef PACKET_HANDLER_MANAGER_HPP
#define PACKET_HANDLER_MANAGER_HPP

#define BOOST_LOG_DYN_LINK 1

#include <memory>
#include <string>
#include <map>
#include <utility>

#include "packet_handler.hpp"
#include "register_handler.hpp"
#include "auth_handler.hpp"

#include "../../database/users_db_manager.hpp"

#include <boost/log/trivial.hpp>

namespace net
{
    namespace packet
    {
        class packet_handler_manager
        {
        public:
            static void register_handler(const std::string& key, std::unique_ptr<net::packet::packet_handler>&& handler);
            static std::pair<bool, std::string> handle_packet(const std::string& key, const std::string& packet_data, db::users_db_manager& database, 
                boost::asio::ip::tcp::socket&);
            static void init();
        private:
            static std::map<std::string, std::unique_ptr<net::packet::packet_handler>> handlers;
        };
    }
}

#endif