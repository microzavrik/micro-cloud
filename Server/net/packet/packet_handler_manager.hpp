#ifndef PACKET_HANDLER_MANAGER_HPP
#define PACKET_HANDLER_MANAGER_HPP

#include <memory>
#include <string>
#include <map>

#include "packet_handler.hpp"
#include "../../database/users_db_manager.hpp"

#include "register_handler.hpp"
#include "auth_handler.hpp"

namespace net
{
    namespace packet
    {
        class packet_handler_manager
        {
        public:
            static void register_handler(const std::string& key, std::unique_ptr<net::packet::packet_handler>&& handler);
            static void handle_packet(const std::string& key, const std::string& packet_data, db::users_db_manager* database = nullptr);
            static void init();
        private:
            static std::map<std::string, std::unique_ptr<packet_handler>> handlers;
        };
    }
}

#endif