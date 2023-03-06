#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include "headers.hpp"

#define BUFFSIZE 512
#define _EOF_ -1

class	scanner {

	const char*	_start;
	const char*	_current;
	ssize_t		_count;

	public:

	scanner(const char* buff, ssize_t count) :
		_start(buff),
		_current(buff),
		_count(count)
		{ }

	int	get(void)
	{
		if (_count == 0)
			return (_EOF_);
		_count--;
		return (*_current++);
	}

	void	unget(void)
	{
		_current--;	
		_count++;
	}

	size_t	count(void)
	{
		return (_current - _start);
	}

};

#endif
