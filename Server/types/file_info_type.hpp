#ifndef FILE_INFO_TYPE_HPP
#define FILE_INFO_TYPE_HPP

#include <string>
#include <cstdint>

namespace types
{
    struct file_info_type
    {
        std::string file_name;
        std::string file_extension;
        uint64_t file_size;
    };
}

#endif