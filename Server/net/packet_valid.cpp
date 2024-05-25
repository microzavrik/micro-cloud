#include "packet_valid.hpp"

#include <nlohmann/json.hpp>

namespace net
{
    bool valid_packet(const std::string& packet_data)
    {
        try
        {
            nlohmann::json j = nlohmann::json::parse(packet_data);

            if(j.contains("packet_type")) {
                std::string packet_type = j["packet_type"].get<std::string>();

                if(packet_type == "auth") {
                    if(j.contains("username") && j.contains("password")) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else if(packet_type == "reg") {
                    if(j.contains("reg_username") && j.contains("reg_password")) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else if(packet_type == "list") {
                    // 
                }
                else if(packet_type == "push") {
                    //
                }
                else if(packet_type == "down") {
                    //
                }
                else if(packet_type == "del") {
                    //
                }
            }
        }
        catch (const nlohmann::json::parse_error& e)
        {
            return false;
        }

        return false;
    }
}