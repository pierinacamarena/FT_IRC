#ifndef _SERVER_HPP_
#define _SERVER_HPP_

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
#include "SocketServer.hpp"

class Server
{
	private:
		int	fd_count;
		int	fd_size;
		int	new_fd;
		struct pollfd* pfds = new pollfd[5];
		int _listener;
		struct sockaddr_storage	client_address;
		socklen_t size_c_address;
		char buff[256];
		char remoteIP[INET6_ADDRSTRLEN];

	public:
	
	Server(int listener, int size)
	{
		_listener = listener;
		fd_count = 0;
		fd_size = size;
		memset(pfds, 0, sizeof(struct pollfd) * 5);
	}

	void add_to_pfds(int new_fd)
	{
    	if (fd_count == fd_size) {
        	fd_size *= 2;
        	pfds = (struct pollfd*)realloc(pfds, sizeof(struct pollfd) * (fd_size));
    	}

    	pfds[fd_count].fd = new_fd;
	    pfds[fd_count].events = POLLIN;

    	fd_count++;
	}

	void del_from_pfds(int i)
	{
		pfds[i] = pfds[fd_count - 1];
		fd_count--;
	}
	int	get_fd(int i)
	{
		return pfds[i].fd;
	}

	void	*get_in_addr(struct sockaddr *sa)
	{
		if (sa->sa_family == AF_INET)
			return &(((struct sockaddr_in*)sa)->sin_addr);
		return &(((struct sockaddr_in6*)sa)->sin6_addr);
	}

	void run()
	{
		std::cout << "___________________" << std::endl;
		std::cout << " pfds[0].fd: " << pfds[0].fd << " pfds[0].revents: " << pfds[0].revents << std::endl;
		add_to_pfds(_listener);
		std::cout << " pfds[0].fd: " << pfds[0].fd << " pfds[0].revents: " << pfds[0].revents << std::endl;
		
		while (1)
		{
			int poll_count = poll(pfds, fd_count, -1);

			if (poll_count == -1)
			{
				perror("poll:");
				exit(1);
			}
			for (int i = 0; i < fd_count; i++)
			{
				std::cout << "i: " << i << " pfds[i].fd: " << pfds[i].fd << "pfds[i].revents: " << pfds[i].revents << std::endl;
				if (pfds[i].revents & POLLIN)
				{
					if (pfds[i].fd == _listener)
					{
						std::cout << "I am in the listener" << std::endl;
						size_c_address = sizeof(client_address);
						new_fd = accept(_listener, 
						(struct sockaddr *)&client_address, 
						&size_c_address);
						if (new_fd == -1)
							perror("accept");
						else
						{
							std::cout << "___________________" << std::endl;
							std::cout << "i: " << i << " pfds[i+1].fd: " << pfds[i+1].fd << " pfds[i+1].revents: " << pfds[i+1].revents << std::endl;
							add_to_pfds(new_fd);
							std::cout << "___________________" << std::endl;
							std::cout << "i: " << i << " pfds[i+1].fd: " << pfds[i+1].fd << " pfds[i+1].revents: " << pfds[i+1].revents << std::endl;
							std::cout << "pollserver: new connection from " << inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr*)&client_address), remoteIP, INET6_ADDRSTRLEN) << " on socket: " << new_fd << std::endl;
						}
					}
					else
					{
						std::cout << "I am in the client" << std::endl;
						int numbytes = recv(pfds[i].fd, buff, sizeof(buff), 0);
						int sender_fd = pfds[i].fd;
						if (numbytes <= 0)
						{
							if (numbytes == 0)
								std::cout << "pollserver: socket " << sender_fd << " hung up" << std::endl;
							else
								perror("recv:");
							close(sender_fd);
							del_from_pfds(i);
						}
						else
						{
							for (int j = 0; j < fd_count; j++)
							{
								int dest_fd = pfds[j].fd;
								if (dest_fd != _listener && dest_fd != sender_fd)
								{
									if (send(dest_fd, buff, numbytes, 0) == -1)
										perror("send:");
								}
							}
						}
					}
				}
			}
			std::cout << "_________________" << std::endl;
			std::cout << "left for loop" << std::endl;
		}
	}

};

#endif