# Khai Nguyen
#

# define a target for the application
#
all: tcp_server tcp_client

# define a target to link the application
#
tcp_server: server.cpp function.cpp
	g++ server.cpp function.cpp -o tcp_server

tcp_client: client.cpp
	g++ client.cpp -o tcp_client

# define a target to clean the directory
#
clean:
	rm -f *.o *.exe
#
# end of file
