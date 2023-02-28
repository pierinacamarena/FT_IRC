#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include "SocketServer.hpp"
#include "Client.hpp"

class Server
{
	private:
		std::vector<struct pollfd>	_pfds;
		int 						_listener;
		char						buff[256];
		std::string 				_password;
		std::map<int, Client*>		_clients;


	public:
	
	Server(int listener, std::string password);

	void add_to_pfds(int new_fd);

	void del_from_pfds(int i);

	int	get_fd(int i);

	void	*get_in_addr(struct sockaddr *sa);

	void	accept_connection(size_t location);

	void	receive_send_data(size_t location);

	void	send_data(int numbytes, int sender_fd);

	int		receive_data(size_t location, int *numbytes);

	void run();

};

#endif