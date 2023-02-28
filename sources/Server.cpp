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
	char					remoteIP[INET6_ADDRSTRLEN];
	char 					host[NI_MAXHOST];
	socklen_t				size_c_addr;
	struct sockaddr_storage	c_addr;
	int						new_fd;

	if (DEBUG)
		std::cout << "I am in the listener" << std::endl;
	size_c_addr = sizeof(c_addr);
	new_fd = accept(_listener, (struct sockaddr *)&c_addr, &size_c_addr);
	if (new_fd == -1)
		perror("accept");
	else
	{
		if (DEBUG)
		{
			std::cout << "___________________" << std::endl;
			std::cout << "i: " << location << " pfds[i+1].fd: " << _pfds[location+1].fd << " pfds[i+1].revents: " << _pfds[location+1].revents << std::endl;
		}
		if (DEBUG)
		{
			std::cout << "___________________" << std::endl;
			std::cout << "i: " << location << " pfds[i+1].fd: " << _pfds[location+1].fd << " pfds[i+1].revents: " << _pfds[location+1].revents << std::endl;
		}

		const char *result = inet_ntop(c_addr.ss_family, get_in_addr((struct sockaddr*)&c_addr), remoteIP, INET6_ADDRSTRLEN);
		if (result == NULL) {
			perror("inet_ntop");
			exit(EXIT_FAILURE);
		}
		int err;
		if ((err = getnameinfo((struct sockaddr*)&c_addr, sizeof(c_addr), host, NI_MAXHOST, NULL, 0, 0)) != 0)
			perror("getnameinfo: ");
		else
			std::cout << "Hostname: " << host << std::endl;
		_clients[new_fd] = new Client(new_fd, remoteIP, host);
		add_to_pfds(new_fd);
		std::cout << "pollserver: new connection from " << remoteIP << " on socket: " << new_fd << std::endl;

	}
}

void	Server::receive_send_data(size_t location)
{
	if (DEBUG)
		std::cout << "I am in the client" << std::endl;
	int	numbytes;
	int	sender_fd = receive_data(location, &numbytes);
	if (numbytes > 0)
		send_data(numbytes, sender_fd);
}

void	Server::send_data(int numbytes, int sender_fd)
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

int		Server::receive_data(size_t location, int *numbytes)
{
	*numbytes = recv(_pfds[location].fd, buff, sizeof(buff), 0);
	int sender_fd = _pfds[location].fd;
	if (*numbytes <= 0)
	{
		if (*numbytes == 0)
			std::cout << "pollserver: socket " << sender_fd << " hung up" << std::endl;
		else
			perror("recv:");
		close(sender_fd);
		del_from_pfds(location);
	}
	return (sender_fd);
}


void	Server::run()
{
	if (DEBUG)
	{
		std::cout << "___________________" << std::endl;
		std::cout << " pfds[0].fd: " << _pfds[0].fd << " pfds[0].revents: " << _pfds[0].revents << std::endl;
		std::cout << " pfds[0].fd: " << _pfds[0].fd << " pfds[0].revents: " << _pfds[0].revents << std::endl;
		std::cout << "array is empty: " << _pfds.empty() <<  " size: " << _pfds.size() << std::endl;
	}
	while (1)
	{
		int poll_count = poll(&_pfds[0], _pfds.size(), -1);

		if (poll_count == -1)
		{
			perror("poll:");
			exit(1);
		}
		if (DEBUG)
			std::cout << "poll is: " << poll_count << std::endl;
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if (DEBUG)
				std::cout << "i: " << i << " pfds[i].fd: " << _pfds[i].fd << "pfds[i].revents: " << _pfds[i].revents << std::endl;
			if (_pfds[i].revents & POLLIN)
			{
				if (_pfds[i].fd == _listener)
					accept_connection(i);
				else
					receive_send_data(i); //on the client
			}
		}
		if (DEBUG)
		{
			std::cout << "_________________" << std::endl;
			std::cout << "left for loop" << std::endl;
			std::cout << "_________________" << std::endl;
		}
	}
}