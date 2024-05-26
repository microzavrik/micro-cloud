#include "packet_handler.hpp"

namespace net
{
    namespace packet
    {
        class auth_handler : net::packet::packet_handler
        {
        public:
            std::pair<bool, std::string> handle(const std::string& packet_data, db::users_db_manager* = nullptr) override;
        };
    }
}
