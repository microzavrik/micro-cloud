#include "packet_handler.hpp"

namespace net
{
    namespace packet
    {
        bool packet_handler::has_key(const nlohmann::json& json_data, const std::string& key)
        {
            return json_data.contains(key);
        }

        template <typename T>
        T packet_handler::get_value(const nlohmann::json& json_data, const std::string& key) const
        {
            return json_data.at(key).get<T>();
        }
    }
}