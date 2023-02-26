/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:46:46 by pcamaren          #+#    #+#             */
/*   Updated: 2023/02/26 20:28:47 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SocketServer.hpp"
#include "../includes/Server.hpp"


int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv <port> <password>";
		exit(1);
	}
	SocketServer socket_server(av[1]);
	int	listener = socket_server.get_listener();
	Server server(listener, av[2]);
	server.run();
	return 0;
}