#include "register_handler.hpp"

#include <iostream>
#include <string>

namespace net
{
    namespace packet
    {
        std::pair<bool, std::string> register_handler::handle(const std::string& packet_data, db::users_db_manager& database, 
            boost::asio::ip::tcp::socket& socket)
        {
            nlohmann::json json_data = nlohmann::json::parse(packet_data);

            bool result = database.push_user(types::user_type{json_data["username"], json_data["password"]});
            
            if(result) {
                return std::make_pair(true, "Sucessfully registration");
            }
            else {
                return std::make_pair(false, "Losed registration");
            }

            return std::make_pair(false, "Handle Error Message");
        }
    }
}