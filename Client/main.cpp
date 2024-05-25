#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <random>

using namespace boost::asio;
using namespace boost::system;
using json = nlohmann::json;

int main()
{
    // Create a random username and password
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);

    std::string username = "user" + std::to_string(dist(mt));
    std::string password = "pass" + std::to_string(dist(mt));

    // Create a JSON object
    json j;
    j["packet_type"] = "auth";
    j["username"] = username;
    j["password"] = password;

    // Convert the JSON object to a string
    std::string json_string = j.dump();

    // Create an Asio io_context
    io_context ioc;

    // Create a TCP socket
    ip::tcp::socket socket(ioc);

    // Connect to the server
    ip::tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 8080);
    socket.connect(endpoint);

    // Send the JSON string to the server
    boost::asio::write(socket, boost::asio::buffer(json_string));

    // Close the socket
    socket.close();

    return 0;
}