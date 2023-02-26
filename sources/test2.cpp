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


void	*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	SocketServer socket_server("9034");
	int	listener = socket_server.get_listener();
	Server server(listener, 5);
	server.run();
	return 0;
}