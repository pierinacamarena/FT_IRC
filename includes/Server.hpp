#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "SocketServer.hpp"

class Server
{
	private:
		std::vector<struct pollfd>	_pfds;
		int							new_fd;
		int 						_listener;
		struct sockaddr_storage		client_address;
		socklen_t					size_c_address;
		char						buff[256];
		char						remoteIP[INET6_ADDRSTRLEN];
		std::string 				_password;

	public:
	
	Server(int listener, std::string password);

	void add_to_pfds(int new_fd);

	void del_from_pfds(int i);

	int	get_fd(int i);

	void	*get_in_addr(struct sockaddr *sa);

	void	accept_connection(size_t location);

	void run();

};

#endif