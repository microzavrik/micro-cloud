#ifndef AUTH_HANDLER_HPP
#define AUTH_HANDLER_HPP

#include "packet_handler.hpp"

namespace net
{
    namespace packet
    {
        class auth_handler : public net::packet::packet_handler
        {
        public:
            std::pair<bool, std::string> handle(const std::string& packet_data, db::users_db_manager& database,  boost::asio::ip::tcp::socket& socket) override;
        };
    }
}

#endif