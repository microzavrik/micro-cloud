#ifndef PACKET_HANDLER_HPP
#define PACKET_HANDLER_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <utility>

#include "../../database/users_db_manager.hpp"

#include <boost/asio.hpp>

namespace net
{
    namespace packet
    {
        class packet_handler
        {
        public:
            virtual std::pair<bool, std::string> 
            handle(const std::string& packet_data, db::users_db_manager& database, boost::asio::ip::tcp::socket& socket) = 0;
        protected:
            bool has_key(const nlohmann::json& json_data, const std::string& key);
            template <typename T> T get_value(const nlohmann::json& json_data, const std::string& key) const;
        };
    }
}


#endif