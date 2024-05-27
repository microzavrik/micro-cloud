#include "file_list_handler.hpp"

#include <iostream>
#include <string>

namespace net
{
    namespace packet
    {
        std::pair<bool, std::string> file_list_handler::handle(const std::string& packet_data, db::users_db_manager& database, 
            boost::asio::ip::tcp::socket& socket)
        {
            nlohmann::json json_data = nlohmann::json::parse(packet_data);
        }
    }
}