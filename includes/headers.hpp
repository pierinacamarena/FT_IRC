#ifndef _HEADERS_HPP_
#define _HEADERS_HPP_

#include <netdb.h>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <errno.h>
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
#include <fcntl.h>
#include <iostream>
#include <map>
#include <set>

#ifndef DEBUG
#define DEBUG 0
#endif


// REPLIES
#define RPL_WELCOME 1
#define RPL_UMODEIS 221

// ERROR REPLIES
#define ERR_UNKNOWNCOMMAND 421
#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NOTREGISTERED 451
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTERED 462
#define ERR_PASSWDMISMATCH 464
#define ERR_RESTRICTED 484
#define ERR_UMODEUNKNOWNFLAG 501
#define ERR_USERSDONTMATCH 502


typedef std::vector<struct pollfd>::iterator pfd_iter;

#endif
