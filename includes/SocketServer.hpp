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
		// {
		// 	memset(&hints, 0, sizeof hints);
		// 	hints.ai_family = AF_UNSPEC;
		// 	hints.ai_socktype = SOCK_STREAM;
		// 	hints.ai_flags = AI_PASSIVE;

		// 	int status;
		// 	if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
		// 	{
		// 		perror("getaddrinfo:");
		// 		exit(1);
		// 	}
		// 	for (p = servinfo; p != NULL; p = p->ai_next)
		// 	{
		// 		if ((listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
		// 			continue;
		// 		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		// 		if ((status = bind(listener, p->ai_addr, p->ai_addrlen)) == -1)
		// 			continue;
		// 		break;
		// 	}
		// 	freeaddrinfo(servinfo);
		// 	if (p == NULL)
		// 	{
		// 		std::cerr << "ERROR: failed to bind socket" << std::endl;
		// 		exit(1);
		// 	}
		// 	if (listen(listener, 10) == -1)
		// 	{
		// 		std::cerr << "ERROR: failed to listen on socket" << std::endl;
		// 		exit(1);
		// 	}
		// }

		~SocketServer();
		// {
		// 	std::cout << "calling destructor" << std::endl;
		// 	// close(listener);
		// }

		int	get_listener(void) const;
		// {
		// 	return listener;
		// }
};

#endif