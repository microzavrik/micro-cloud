#include "packet_file_info_return.hpp"

#include <nlohmann/json.hpp>
#include <iostream>


namespace net
{
    types::file_info_type packet_file_info_return(const std::string& packet_data)
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(packet_data);
            std::string file_name = j["file_name"];
            std::string file_extension = j["file_extension"];
            std::string file_size = j["file_size"];
            return types::file_info_type{file_name, file_extension, std::stoull(file_size)};
        }
        catch(const nlohmann::json::parse_error& e)
        {
            std::cout << "Error Packet File Info return" << std::endl;
        }
    }
}
