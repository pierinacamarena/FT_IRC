#include <string>

struct	token
{
	int			_type;
	std::string	_lexeme;

	token(int type) :
		_type(type),
		_lexeme()
		{}

	token(int type, const std::string& lexeme) :
		_type(type),
		_lexeme(lexeme)
		{}
	
};