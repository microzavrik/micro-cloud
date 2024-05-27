#include "packet_handler_manager.hpp"

namespace net
{
    namespace packet
    {
        std::map<std::string, std::unique_ptr<packet_handler>> packet_handler_manager::handlers;

        void packet_handler_manager::register_handler(const std::string& key, std::unique_ptr<net::packet::packet_handler>&& handler)
        {
            BOOST_LOG_TRIVIAL(info) << "Registered " << key << " packet";
            handlers[key] = std::move(handler);
        }

        std::pair<bool, std::string> packet_handler_manager::handle_packet(const std::string& key, const std::string& packet_data, db::users_db_manager& database,
            boost::asio::ip::tcp::socket& socket)
        {
            if(handlers.find(key) != handlers.end()) {
                BOOST_LOG_TRIVIAL(info) << "Call " << key << " packet handler";
                return handlers[key]->handle(packet_data, database, socket);
            }
            else {
                std::cout << "Handler not found for key: " << key << std::endl;
            }

            return std::make_pair(false, "Packet handler error");
        }

        void packet_handler_manager::init()
        {
            register_handler("reg", std::make_unique<net::packet::register_handler>());
            register_handler("auth", std::make_unique<net::packet::auth_handler>());       
        }
    }
}