#include "packet_type_return.hpp"

#include <nlohmann/json.hpp>

namespace net
{
    std::string packet_return_type(const std::string& packet_data)
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(packet_data);
            return j["packet_type"];
        }
        catch (const nlohmann::json::parse_error& e)
        {
            return "error";
        }

        return "error";
    }
}