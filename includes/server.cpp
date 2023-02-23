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

void add_to_pfds(struct pollfd **pfds, int newfd, int *fd_count, int *fd_size) {
    if (*fd_count == *fd_size) {
        *fd_size *= 2;
        *pfds = (struct pollfd*)realloc(*pfds, sizeof(struct pollfd) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // Check ready-to-read

    (*fd_count)++;
}

void del_from_pfds(struct pollfd *pfds, int i, int *fd_count) {
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count - 1];

    // Decrease the count of total sockets
    (*fd_count)--;
}

int main(void)
{
	// Poll pfds;
	int	listener, new_fd;
	struct sockaddr_storage	client_address;
	socklen_t size_c_address;
	char buff[256];
	char remoteIP[INET6_ADDRSTRLEN];

	int fd_count = 0;
    int fd_size = 5;

	pollfd* pfds = new pollfd[fd_size];
	if ((listener = setup_listener()) == -1)
	{
		std::cerr << "Error: failed to get listening socket" << std::endl;
		std::exit(1);
	}

	add_to_pfds(&pfds, listener, &fd_count, &fd_size);

	for(;;)
	{
		int poll_count = poll(pfds, fd_count, -1);

		if (poll_count == -1)
		{
			perror("poll:");
			exit(1);
		}
		for (int i = 0; i < fd_count; i++)
		{
			if(pfds[i].fd & POLLIN)
			{
				if (pfds[i].fd == listener)
				{
					size_c_address = sizeof(client_address);
					new_fd = accept(listener, (struct sockaddr *)&client_address, &size_c_address);
					if (new_fd == -1)
						perror("accept");
					else
					{
						add_to_pfds(&pfds, new_fd, &fd_count, &fd_size);
						std::cout << "pollserver: new connection from " << inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr*)&client_address), remoteIP, INET6_ADDRSTRLEN) << "on socket: " << new_fd << std::endl;

					}
				}
				else
				{
					int numbytes = recv(pfds[i].fd, buff, sizeof(buff), 0);

					int sender_fd = pfds[i].fd;

					if (numbytes <= 0)
					{
						if (numbytes == 0)
							std::cout << "pollserver: socket " << sender_fd << " hung up" << std::endl;
						else
							perror("recv:");
						close(pfds[i].fd);
						del_from_pfds(pfds, i, &fd_count);
					}
					else
					{
						for (int j = 0; j < fd_count; j++)
						{
							int dest_fd = pfds[j].fd;
							if (dest_fd != listener && dest_fd != sender_fd)
							{
								if (send(dest_fd, buff, numbytes, 0) == -1)
									perror("send:");
							}
						}
					}
				}
			}
		}
	}
	return 0;
}