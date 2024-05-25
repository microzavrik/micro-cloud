#ifndef USERS_DB_MANAGER_HPP
#define USERS_DB_MANAGER_HPP

#define BOOST_LOG_DYN_LINK 1

#include <pqxx/pqxx>
#include <boost/log/trivial.hpp>

#include <iostream>
#include <string>
#include <cstdint>

#include "../types/user_type.hpp"

using result = bool;
using cstring = const std::string;

namespace db
{   
    class users_db_manager
    {
    public:
        users_db_manager(cstring db_name, cstring table_name, cstring db_user, cstring db_password,
            cstring db_host, int32_t db_port);
        result database_check(const char* db_name) const;
        result table_check() const;
        result create_table() const;
        result push_user(const types::user_type) const;
        result avaliable_user(const types::user_type) const;
        result user_verification(const types::user_type)const;
        result set_memory_availability(const types::user_type) const;
        result delete_user(const types::user_type) const;
    private:
        std::string db_name_;
        std::string table_name_;
        std::string db_user_;
        std::string db_password_;
        std::string db_host_;
        int32_t db_port_;
    };
}

#endif