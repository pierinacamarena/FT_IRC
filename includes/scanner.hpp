#ifndef _SCANNERHPP
#define _SCANNERHPP

#include <string>

class  scanner
{
	private:

	std::string _message;
    std::string::const_iterator start;
    std::string::const_iterator current;
	// scanner() {}

	public:

    scanner(const std::string &message)
    {
		_message = message;
		start = message.begin();
		current = message.begin();
	}

	int	getc()
	{
		return(*current++);
	}

    void set_start() {
		start = current;
    }

	std::string get_substr()
	{
		return (std::string(start, current));
	}

	private:

};

#endif