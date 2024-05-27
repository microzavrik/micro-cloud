#include "auth_handler.hpp"

#include <iostream>
#include <string>

namespace net
{
    namespace packet
    {
        std::pair<bool, std::string> auth_handler::handle(const std::string& packet_data, db::users_db_manager& database,  
            boost::asio::ip::tcp::socket& socket)
        {
            nlohmann::json json_data = nlohmann::json::parse(packet_data);

            std::cout << "Packet data: " << json_data << std::endl;
            std::cout << "Username: " << json_data["username"] << ", " << "Password: " << json_data["password"] << std::endl;

            bool result = database.user_verification(types::user_type{json_data["username"], json_data["password"]});
            
            if(result) {
                return std::make_pair(true, "Sucessfully verification");
            }
            else {
                return std::make_pair(false, "Losed verification");
            }

            return std::make_pair(false, "Handle Error Message");
        }
    }
}