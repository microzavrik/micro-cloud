#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <random>
#include <memory>

using namespace boost::asio;
using namespace boost::system;
using json = nlohmann::json;

class AsyncClient : public std::enable_shared_from_this<AsyncClient> {
public:
    AsyncClient(io_context& ioc, const std::string& host, int port)
        : ioc_(ioc), socket_(ioc), endpoint_(ip::address::from_string(host), port) {}

    void start() {
        connect();
        read();
    }

    void send_message(const std::string& message) {
        auto self = shared_from_this();
        boost::asio::async_write(socket_, boost::asio::buffer(message),
            [&](const boost::system::error_code& ec, size_t /*length*/) {
                if (!ec) {
                    std::cout << "Message sent: " << message << std::endl;
                } else {
                    std::cerr << "Error sending message: " << ec.message() << std::endl;
                }
            });
    }

private:
    void connect() {
        auto self = shared_from_this();
        socket_.async_connect(endpoint_,
            [this, self](const boost::system::error_code& ec) {
                if (!ec) {
                    std::cout << "Connected to the server." << std::endl;
                } else {
                    std::cerr << "Error connecting to the server: " << ec.message() << std::endl;
                }
            });
    }

    void read() {
        auto self = shared_from_this();
        socket_.async_read_some(boost::asio::buffer(buffer_),
            [this, self](const boost::system::error_code& ec, size_t length) {
                if (!ec) {
                    std::string message(buffer_.data(), length);
                    std::cout << "Received message: " << message << std::endl;
                    read();
                } else {
                    std::cerr << "Error reading from the server: " << ec.message() << std::endl;
                }
            });
    }

    io_context& ioc_;
    ip::tcp::socket socket_;
    ip::tcp::endpoint endpoint_;
    std::array<char, 1024> buffer_;
};

int main() {
    // Create a random username and password
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 1000000);

    std::string username = "user" + std::to_string(dist(mt));
    std::string password = "pass" + std::to_string(dist(mt));

    // Create a JSON object
    json j;
    j["packet_type"] = "push_file";
    j["file_name"] = "3423424";
    j["file_extension"] = ".jpg";
    j["file_size"] = "123123231";

    // Convert the JSON object to a string
    std::string json_string = j.dump();

    // Create an Asio io_context
    io_context ioc;

    // Create an AsyncClient instance and start it
    auto client = std::make_shared<AsyncClient>(ioc, "127.0.0.1", 8080);
    client->start();

    // Send a message to the server
    client->send_message(json_string);

    // Run the Asio io_context
    ioc.run();

    return 0;
}