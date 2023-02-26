#include "../includes/SocketServer.hpp"

SocketServer::SocketServer(const char *port)
{
	yes = 1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int status;
	if ((status = getaddrinfo(NULL, port, &hints, &servinfo)) != 0)
	{
		perror("getaddrinfo:");
		exit(1);
	}
	socket_bind();
	socket_listen();
}

SocketServer::~SocketServer()
{
	std::cout << "here here here" << std::endl;
	if (listener > 0)
	{
		shutdown(listener, 2);
		close(listener);
	}
}

void	SocketServer::socket_bind()
{
	int	status;
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
			continue;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if ((status = bind(listener, p->ai_addr, p->ai_addrlen)) == -1)
			continue;
		break;
	}
		freeaddrinfo(servinfo);
	if (p == NULL)
	{
		std::cerr << "ERROR: failed to bind socket" << std::endl;
		exit(1);
	}
}

void	SocketServer::socket_listen()
{
		if (listen(listener, 10) == -1)
	{
		std::cerr << "ERROR: failed to listen on socket" << std::endl;
		exit(1);
	}
}

int	SocketServer::get_listener(void) const
{
	return listener;
}
