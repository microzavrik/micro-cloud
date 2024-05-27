#ifndef PACKET_FILE_INFO_RETURN_HPP
#define PACKET_FILE_INFO_RETURN_HPP

#include "../types/file_info_type.hpp"
#include <string>

namespace net
{
    types::file_info_type packet_file_info_return(const std::string& packet_data);
}

#endif