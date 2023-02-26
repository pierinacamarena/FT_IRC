#include "../includes/Server.hpp"

Server::Server(int listener, std::string password) : _listener(listener), _password(password)
{
	_listener = listener;
	std::cout << "Password: " << _password << std::endl;
	_pfds.push_back(pollfd());
	_pfds.back().fd = listener;
	_pfds.back().events = POLLIN;
	_pfds.back().revents = 0;
}

void Server::add_to_pfds(int new_fd)
{
	_pfds.push_back(pollfd());
	_pfds.back().fd = new_fd;
	_pfds.back().events = POLLIN;
	_pfds.back().revents = 0;
}

void Server::del_from_pfds(int i)
{
	_pfds.erase(_pfds.begin() + i);
}

int	Server::get_fd(int i)
{
	return _pfds[i].fd;
}

void	*Server::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void	Server::accept_connection(size_t location)
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
		std::cout << "i: " << location << " pfds[i+1].fd: " << _pfds[location+1].fd << " pfds[i+1].revents: " << _pfds[location+1].revents << std::endl;
		add_to_pfds(new_fd);
		std::cout << "___________________" << std::endl;
		std::cout << "i: " << location << " pfds[i+1].fd: " << _pfds[location+1].fd << " pfds[i+1].revents: " << _pfds[location+1].revents << std::endl;
		std::cout << "pollserver: new connection from " << inet_ntop(client_address.ss_family, get_in_addr((struct sockaddr*)&client_address), remoteIP, INET6_ADDRSTRLEN) << " on socket: " << new_fd << std::endl;
	}
}

void	Server::run()
{
	std::cout << "___________________" << std::endl;
	std::cout << " pfds[0].fd: " << _pfds[0].fd << " pfds[0].revents: " << _pfds[0].revents << std::endl;
	std::cout << " pfds[0].fd: " << _pfds[0].fd << " pfds[0].revents: " << _pfds[0].revents << std::endl;
	std::cout << "array is empty: " << _pfds.empty() <<  " size: " << _pfds.size() << std::endl;
	while (1)
	{
		int poll_count = poll(&_pfds[0], _pfds.size(), -1);

		if (poll_count == -1)
		{
			perror("poll:");
			exit(1);
		}
		std::cout << "poll is: " << poll_count << std::endl;
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			std::cout << "i: " << i << " pfds[i].fd: " << _pfds[i].fd << "pfds[i].revents: " << _pfds[i].revents << std::endl;
			if (_pfds[i].revents & POLLIN)
			{
				if (_pfds[i].fd == _listener)
					accept_connection(i);
				else
				{
					std::cout << "I am in the client" << std::endl;
					int numbytes = recv(_pfds[i].fd, buff, sizeof(buff), 0);
					int sender_fd = _pfds[i].fd;
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
						for (size_t j = 0; j < _pfds.size(); j++)
						{
							int dest_fd = _pfds[j].fd;
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
		std::cout << "_________________" << std::endl;
	}
}