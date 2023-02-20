#ifndef _LEXER_HPP
#define _LEXER_HPP

#include <string>
#include <cctype>
#include "scanner.hpp"
#include "token.hpp"

#define ERROR_TOKEN 2
class  lexer
{
	private:

	scanner _scanner;

	public:

	token	get_token()
	{
		//command
	}
	
	private:

	token	get_command()
	{
		int	c;
		std::string command;

		c = _scanner.getc();
		if (isalpha(c))
		{
			while (isalpha(c))
				c = _scanner.getc();
			command = _scanner.get_substr();
			_scanner.set_start();
			// return (_scanner.get_substr());
		}
		else if (isdigit(c))
		{
			int i= 0;
			while (isdigit(c) && i < 2)
			{
				c = _scanner.getc();
				i++;
			}
			command = _scanner.get_substr();
			_scanner.set_start();
			// return (_scanner.get_substr());
		}

	}



};

#endif