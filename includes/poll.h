#ifndef _POLL_HPP_
#define _POLL_HPP_

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

class poll
{
	private:

	std::vector<struct pollfd> _pollfd;
	int	_size;
	int	_count;
	
	public:

	poll()
	{
		_pollfd.reserve(5);
		_size = 5;
		_count = 0;
	}

	poll(int start_size)
	{
		_pollfd.reserve(start_size);
		_size = start_size;
		_count = 0;
	}

	int		get_size(void)
	{
		return _size;
	}

	int		get_count(void)
	{
		return _count;
	}

	void	add_fd(int new_fd, int fd_count)
	{
		if (fd_count == _size)
		{
			_pollfd.reserve(2 * _size);
			_size = _pollfd.capacity();
		}
		_pollfd[fd_count].fd = new_fd;
		_pollfd[fd_count].events = POLLIN;
		_count++;
	}

	void	delete_fd(int i)
	{
		_pollfd[i] = _pollfd[_count - 1];
		_count--;
	}

};

#endif