#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "headers.hpp"

class Client
{
	private:
		int			_fd;
		int			_last_ping;

		std::string _realname;
		std::string	_username;
		std::string _nickname;
		std::string	_old_nickname;
		std::string _hostaddr;
		std::string	_hostname;

		bool		_connected;
		bool		_operator;
	public:

		Client(int fd, char c_addr[], char host[]) : _fd(fd), _hostaddr(c_addr), _hostname(host)
		{
			if ((fcntl(fd, F_SETFL, O_NONBLOCK)) < 0)
			{
				perror("fcntl: ");
				exit(1);
			}

		}

		void	set_realname(std::string realname) { _realname = realname; }
		void	set_username(std::string username) { _username = username; }
		void	set_nickname(std::string nickname) { _old_nickname = _username; _nickname = nickname;}
		void	set_hostname(std::string hostname) { _hostname = hostname; }

		void	set_fd(int fd) { _fd = fd; }
		void	set_connected(void) { _connected = true; }

		void	make_operator(void) { _operator = true; }

		const std::string	&get_username(void) const { return _username; }
		const std::string	&get_nickname(void) const { return _nickname; }
		const std::string	&get_old_nickname(void) const { return _old_nickname; }
		const std::string	&get_hostname(void) const { return _hostname; }
		const std::string	&get_hostaddr(void) const { return _hostaddr; }
		
		int					get_fd(void) const { return _fd; }
		int					get_last_ping(void) const { return _last_ping; }
		
		bool				is_operator(void) { return _operator; }
};

#endif