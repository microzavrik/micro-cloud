#include "users_db_manager.hpp"

namespace db
{
    users_db_manager::users_db_manager(cstring db_name, cstring table_name, cstring db_user, cstring db_password,
            cstring db_host, int32_t db_port) :
            db_name_(db_name),
            table_name_(table_name),
            db_user_(db_user),
            db_password_(db_password),
            db_host_(db_host),
            db_port_(db_port)
            { }

    result users_db_manager::database_check(const char* db_name) const
    {
        try
        {
            pqxx::connection conn("dbname=" + db_name_ + " user=" + db_user_ + " password=" + db_password_ + " host=" + db_host_ + " port=" + std::to_string(db_port_));

            if(conn.is_open()) {
                BOOST_LOG_TRIVIAL(info) << "Database exists: " << conn.dbname();
                conn.disconnect();
                return true;
            }
            else {
                BOOST_LOG_TRIVIAL(error) << "Database does not exist";
                return false;
            }
        }
        catch(const std::exception& ex)
        {
            BOOST_LOG_TRIVIAL(error) << "Database does not exist";
            return false;
        }
    }

    result users_db_manager::table_check() const
    {
        try
        {
            pqxx::connection conn("dbname=" + db_name_ + " user=" + db_user_ + " password=" + db_password_ + " host=" + db_host_ + " port=" + std::to_string(db_port_));
            pqxx::work wrk(conn);
            pqxx::result res = wrk.exec("SELECT EXISTS (SELECT 1 FROM information_schema.tables WHERE table_name = '" + table_name_ + "');");
            bool table_exist = res[0][0].as<bool>();
            wrk.commit();
            conn.disconnect();
            return table_exist;
        }
        catch(const std::exception& ex)
        {
            BOOST_LOG_TRIVIAL(error) << ex.what();
            return false;
        }
    }

    result users_db_manager::create_table() const
    {
        try
        {
            pqxx::connection conn("dbname=" + db_name_ + " user=" + db_user_ + " password=" + db_password_ + " host=" + db_host_ + " port=" + std::to_string(db_port_));
            pqxx::work wrk(conn);
            wrk.exec("CREATE TABLE IF NOT EXISTS " + table_name_ + " (id SERIAL PRIMARY KEY, username VARCHAR(50), password VARCHAR(50), available_memory INTEGER);");
            wrk.commit();
            conn.disconnect();

            return true;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    result users_db_manager::push_user(const types::user_type user) const
    {
        try
        {
            pqxx::connection conn("dbname=" + db_name_ + " user=" + db_user_ + " password=" + db_password_ + " host=" + db_host_ + " port=" + std::to_string(db_port_));
            pqxx::work wrk(conn);
            wrk.exec("INSERT INTO " + table_name_ + " (username, password, available_memory) VALUES ('" + user.username_ + "', '" + user.password_ + "', 5);");
            wrk.commit();
            conn.disconnect();
            return true;
        }
        catch(const std::exception& ex)
        {
            BOOST_LOG_TRIVIAL(error) << ex.what();
            return false;
        }
    }

    result users_db_manager::avaliable_user(const types::user_type user) const
    {
        try
        {
            pqxx::connection C("dbname=" + db_name_ + " user=" + db_user_ + " password=" + db_password_ + " host=" + db_host_ + " port=" + std::to_string(db_port_));
            pqxx::work W(C);
            pqxx::result R = W.exec("SELECT EXISTS (SELECT 1 FROM " + table_name_ + " WHERE username = '" + user.username_ + "' AND password = '" + user.password_ + "');");
            bool userExists = R[0][0].as<bool>();
            W.commit();
            C.disconnect();
            return userExists;
        }
        catch (const std::exception& ex)
        {
            BOOST_LOG_TRIVIAL(error) << ex.what();
            return false;
        }
    }

    result users_db_manager::user_verification(const types::user_type user) const
    {
        try
        {
            pqxx::connection conn("dbname=" + db_name_ + " user=" + db_user_ + " password=" + db_password_ + " host=" + db_host_ + " port=" + std::to_string(db_port_));
            pqxx::work wrk(conn);
            pqxx::result res = wrk.exec("SELECT COUNT(*) FROM " + table_name_ + " WHERE username = '" + user.username_ + "' AND password = '" + user.password_ + "';");
            int count = res[0][0].as<int>();
            wrk.commit();
            conn.disconnect();
            return count > 0;
        }
        catch (const std::exception& ex)
        {
            BOOST_LOG_TRIVIAL(error) << ex.what();
            return false;
        }
    }
}