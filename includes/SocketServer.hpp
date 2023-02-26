#ifndef _SOCKETSERVER_HPP_
#define _SOCKETSERVER_HPP_

#include "headers.hpp"

class SocketServer
{
	private:
		struct addrinfo hints;
		struct addrinfo *servinfo;
		struct addrinfo *p;
		int				listener;
		int				yes;
		const char*		_port;
		// char*		_psswd;

		void	socket_bind();

		void	socket_listen();
	public:
		SocketServer(const char *port);

		virtual ~SocketServer();

		int		get_listener(void) const;
};

#endif