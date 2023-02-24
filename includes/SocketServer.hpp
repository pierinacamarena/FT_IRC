#ifndef _SOCKETSERVER_HPP_
#define _SOCKETSERVER_HPP_

#include <netdb.h>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>

class SocketServer
{
	private:
		struct addrinfo hints;
		struct addrinfo *servinfo;
		struct addrinfo *p;
		int				listener;
		int				yes = 1;

	public:
		SocketServer(const char *port);

		~SocketServer();

		int	get_listener(void) const;
};

#endif