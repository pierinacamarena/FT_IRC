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
#include "poll.h"
#include <iostream>

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

void	*get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	Poll pfds;
	int	listener, new_fd;
	struct sockaddr_storage	client_address;
	socklen_t size_c_address;
	char buff[256];
	char remoteIP[INET6_ADDRSTRLEN];

	if ((listener = setup_listener()) == -1)
	{
		std::cerr << "Error: failed to get listening socket" << std::endl;
		std::exit(1);
	}

	pfds.add_fd(listener, 0);

	for (int k = 0; k < 50; k++)
	{
		if (poll(&pfds.get_vector()[0], pfds.get_count(), -1) == -1)
		{
			perror("poll");
			exit(1);
		}
		std::cout << "here" << std::endl;
		for (int i = 0; i < pfds.get_count(); i++)
		{
			std::cout << "ENTERING HEREEEE" << std::endl;
			std::cout << "count is: " << pfds.get_count() << std::endl;
			std::cout << "pfds.revents is: " << pfds.get_vector()[i].revents << std::endl;
			if (pfds.get_vector()[i].revents & POLLIN)
			{
				if (pfds.get_vector()[i].fd == listener)
				{			
					size_c_address = sizeof client_address;
					if ((new_fd = accept(listener, (struct sockaddr *)&client_address, &size_c_address)) == -1)
						perror("accept:");
					else
					{
						pfds.add_fd(new_fd, pfds.get_count());

						std::cout << "pollserver: new connection from " << inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr*)&client_address), remoteIP, INET6_ADDRSTRLEN) << "on socket " << new_fd << std::endl;
					}
				}
				else
				{
					int numbytes = recv(pfds.get_vector()[i].fd, buff, sizeof buff, 0);

					int sender_fd = pfds.get_vector()[i].fd;

					if (numbytes <= 0)
					{
						if (numbytes == 0)
							std::cout << "pollserver: socket " << sender_fd << " hung up" << std::endl;
						else
							perror("recv:");
						close(pfds.get_vector()[i].fd);
						pfds.delete_fd(i);
					}
					else
					{
						for (int j = 0; j < pfds.get_count(); j++)
						{
							int dest_fd = pfds.get_vector()[j].fd;
							if (dest_fd != listener && dest_fd != sender_fd)
							{
								if (send(dest_fd, buff, numbytes, 0) == -1)
									perror("send");
							}
						}
					}
				}
			}
		}
	}
	return 0;
}