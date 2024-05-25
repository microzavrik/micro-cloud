TARGET= micro_cloud_server.out

CXX = g++ -std=c++17 -O3

SOURCES = main.cpp database/users_db_manager.hpp database/users_db_manager.cpp types/user_type.hpp net/session.hpp net/session.cpp net/server.hpp net/server.cpp net/packet_valid.hpp net/packet_valid.cpp net/packet/packet_handler.hpp net/packet/packet_handler.cpp net/packet/auth_handler.hpp net/packet/auth_handler.cpp net/packet/register_handler.hpp net/packet/register_handler.cpp

LDFLAGS = -lpq -lpqxx -lboost_log -lboost_log_setup -lboost_system -lboost_thread

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)

install:
	cp $(TARGET) /usr/local/bin/

run:
	./$(TARGET) 