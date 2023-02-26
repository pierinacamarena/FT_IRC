#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <poll.h>
#include <iostream>
#include <fcntl.h>
#include "../includes/SocketServer.hpp"
#include "../includes/Server.hpp"


int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv <port> <password>";
		exit(1);
	}
	SocketServer socket_server(av[1], av[2]);
	int	listener = socket_server.get_listener();
	Server server(listener);
	server.run();
	return 0;
}