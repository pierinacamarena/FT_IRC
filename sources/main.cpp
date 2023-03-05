/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:46:46 by pcamaren          #+#    #+#             */
/*   Updated: 2023/03/05 16:52:31 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SocketServer.hpp"
#include "../includes/Server.hpp"
#include "../includes/Data.hpp"


int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv <port> <password>";
		exit(1);
	}
	Data data(av[2]);
	SocketServer socket_server(av[1]);
	int	listener = socket_server.get_listener();
	Server server(listener, &data);
	server.run();
	return 0;
}