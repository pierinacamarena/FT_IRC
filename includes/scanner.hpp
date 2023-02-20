#ifndef _SCANNERHPP
#define _SCANNERHPP

#include <iostream>

class  scanner
{
	private:

    std::string::const_iterator start;
    std::string::const_iterator current;
	// scanner() {}

	public:

    scanner(const std::string &message) : start(message.begin(), current(message.begin()))
    {}

    ~scanner() {}



    void setStart() {
		start = current;
    }

	std::string	get_token()
	{
		//command
		while()
	}

	private:

	//helper function

};

#endif