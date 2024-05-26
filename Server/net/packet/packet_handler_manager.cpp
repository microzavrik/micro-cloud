#include "packet_handler_manager.hpp"

namespace net
{
    namespace packet
    {
        std::map<std::string, std::unique_ptr<packet_handler>> packet_handler_manager::handlers;

        void packet_handler_manager::register_handler(const std::string& key, std::unique_ptr<net::packet::packet_handler>&& handler)
        {
            handlers[key] = std::move(handler);
        }

        void packet_handler_manager::handle_packet(const std::string& key, const std::string& packet_data, db::users_db_manager* database)
        {
            if(handlers.find(key) != handlers.end()) {
                handlers[key]->handle(packet_data, database);
            }
            else {
                std::cout << "Handler not found for key: " << key << std::endl;
            }
        }

        void packet_handler_manager::init()
        {
            // register_handler("auth", std::make_unique<net::packet::auth_handler>());
            register_handler("reg", std::make_unique<net::packet::register_handler>());
        }
    }
}