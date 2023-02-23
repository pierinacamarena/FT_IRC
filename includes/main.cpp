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

// #ifndef PORT
// #define PORT "9034"
// #endif

int	setup_listener(void)
{
	int		status;
	int		listener;
	struct addrinfo hints, *servinfo, *p;
	int		yes=1;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, "9034", &hints, &servinfo)) != 0)
	{
		perror("getaddrinfo: ");
		exit (1);
	}
	
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
		return -1;
	if (listen(listener, 10) == -1)
		return -1;
	
	return (listener);
}

int main(void)
{
	std::vector<struct pollfd> pollfds;

	int	listener, new_fd;
	struct sockaddr_storage	client_address;
	socklen_t size_c_address;
	char buff[256];
	char remoteIP[INET6_ADDRSTRLEN];
	int	pollfd_size = 5;
	int	pollfd_count; = 0
}