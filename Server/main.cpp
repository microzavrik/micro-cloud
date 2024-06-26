#include "net/server.hpp"
#include "database/users_db_manager.hpp"
#include "net/packet/packet_handler_manager.hpp"
#include <boost/asio.hpp>
#include <thread>

int main()
{
    try
    {
        net::packet::packet_handler_manager::init();
        
        db::users_db_manager db("users", "cloud_users", "postgres", "123123", "127.0.0.1", 5433);
        db.database_check("users");
        db.create_table();

        boost::asio::io_context ios;
        net::server* server = new net::server(ios, 8080, db);
        
        std::thread t([&]()
        {
            ios.run();
        });

        ios.run();
        
        t.join();

        delete server; 
    }
    catch(std::exception& ex) 
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    return 0;
}