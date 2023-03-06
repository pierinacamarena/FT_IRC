/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:59:07 by pcamaren          #+#    #+#             */
/*   Updated: 2023/03/06 14:27:15 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Reply.hpp"
void	error_caller(int reply_id, const std::set<int>& dest_fds, const std::string &command, const std::string &identifyer)
{
	std::set<int>::const_iterator it = dest_fds.begin();
	switch (reply_id)
	{
	case ERR_UNKNOWNCOMMAND:
		for (; it != dest_fds.end(); ++it)
			err_unknown_command(*it, command, identifyer);
		break;
	case ERR_NONICKNAMEGIVEN:
		for (; it != dest_fds.end(); ++it)
			err_no_nicknamegive(*it, identifyer);
		break;
	case ERR_ERRONEUSNICKNAME:
		for (; it != dest_fds.end(); ++it)
			err_erroneus_nickname(*it, command, identifyer);
		break;
	case ERR_NICKNAMEINUSE:
		for (; it != dest_fds.end(); ++it)
			err_nickname_inuse(*it, command, identifyer);
		break;
	case ERR_NOTREGISTERED:
		for (; it != dest_fds.end(); ++it)
			err_not_registered(*it, identifyer);
		break;
	case ERR_NEEDMOREPARAMS:
		for (; it != dest_fds.end(); ++it)
			err_need_moreparams(*it, command);
		break;
	case ERR_ALREADYREGISTERED: 
		for (; it != dest_fds.end(); ++it)
			err_already_registered(*it, identifyer);
		break;
	case ERR_PASSWDMISMATCH: 
		for (; it != dest_fds.end(); ++it)
			err_passwd_mistmatch(*it, identifyer);
		break;
	case ERR_RESTRICTED:
		for (; it != dest_fds.end(); ++it)
			err_restricted(*it, identifyer);
		break;
	case RPL_WELCOME:
		for (; it != dest_fds.end(); ++it)
			rpl_welcome_message(*it, identifyer);
	default:
		break;
	}
}


void	reply_caller(int reply_id, std::vector<int> dest_fds, std::string &identifyer)
{
	std::vector<int>::iterator iter = dest_fds.begin();
	switch (reply_id)
	{
	case RPL_WELCOME:
		// std::vector<int>::iterator it = dest_fds.begin();
		iter = dest_fds.begin();
		for (; iter != dest_fds.end(); ++iter)
			rpl_welcome_message(*iter, identifyer);
		break;
	default:
		break;
	}
}

//pass

//    ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
// Done
//nick

//    ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//    ERR_NICKNAMEINUSE               
//    ERR_RESTRICTED
// Done
//USER

// ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED
// Done

// OPER
//            ERR_NEEDMOREPARAMS              RPL_YOUREOPER
//            ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

// USER MODE 

// ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
// ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS

//JOIN

//    ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
//    ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
//    ERR_CHANNELISFULL               ERR_BADCHANMASK
//    ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
//    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
//    RPL_TOPIC


//PART
//    ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//    ERR_NOTONCHANNEL

// CHANNEL MODE
//    ERR_NEEDMOREPARAMS              ERR_KEYSET
//    ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
//    ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
//    RPL_CHANNELMODEIS
//    RPL_BANLIST                     RPL_ENDOFBANLIST
//    RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
//    RPL_INVITELIST                  RPL_ENDOFINVITELIST
//    RPL_UNIQOPIS

// TOPIC
// NAMES
// LIST

// INVITE
// ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
// ERR_NOTONCHANNEL                ERR_USERONCHANNEL
// ERR_CHANOPRIVSNEEDED
// RPL_INVITING                    RPL_AWAY

// KICK
// LERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
// LERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
// LERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL

// PRIVMSG

// ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
// ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
// ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
// ERR_NOSUCHNICK
// RPL_AWAY

// MOTD?
//	RPL_MOTDSTART                   RPL_MOTD
//	RPL_ENDOFMOTD                   ERR_NOMOTD

// STATS?
//	ERR_NOSUCHSERVER
//	RPL_STATSLINKINFO                RPL_STATSUPTIME
//	RPL_STATSCOMMANDS                RPL_STATSOLINE
//	RPL_ENDOFSTATS


// WHO

//ERR_NOSUCHSERVER
// RPL_WHOREPLY                  RPL_ENDOFWHO

// WHOIS

//    ERR_NOSUCHSERVER              ERR_NONICKNAMEGIVEN
//    RPL_WHOISUSER                 RPL_WHOISCHANNELS
//    RPL_WHOISCHANNELS             RPL_WHOISSERVER
//    RPL_AWAY                      RPL_WHOISOPERATOR
//    RPL_WHOISIDLE                 ERR_NOSUCHNICK
//    RPL_ENDOFWHOIS

//WHOWAS

//	ERR_NONICKNAMEGIVEN           ERR_WASNOSUCHNICK
//	RPL_WHOWASUSER                RPL_WHOISSERVER
//	RPL_ENDOFWHOWAS

// KILL
// ERR_NOPRIVILEGES              ERR_NEEDMOREPARAMS
// ERR_NOSUCHNICK                ERR_CANTKILLSERVER

// PING
// ERR_NOORIGIN                  ERR_NOSUCHSERVER

// PONG
// ERR_NOORIGIN                  ERR_NOSUCHSERVER

// USERS
// ERR_NOSUCHSERVER              ERR_FILEERROR
// RPL_USERSSTART                RPL_USERS
// RPL_NOUSERS                   RPL_ENDOFUSERS
// ERR_USERSDISABLED

// ERRORS

//
void	err_unknown_command(int dest_fd, const std::string &command, const std::string &identifyer)
{
	std::string err_message = identifyer + "'\'" + command + " :Unknown command\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

//461
void	err_need_moreparams(int dest_fd, const std::string &command)
{
	std::string err_message = command + " :Not enough parameters\n";
	
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

//462
void	err_already_registered(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + ":Unauthorized command (alredy registered)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// ":Unauthorized command (alredy registered)"
}

void	err_not_registered(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + ":You have not registered\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

//431
void	err_no_nicknamegive(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + ":No nickname given\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// ":No nickname given"
}

// 432
void	err_erroneus_nickname(int dest_fd, const std::string &nickname, const std::string &identifyer)
{
	std::string err_message = identifyer + nickname + " :Erroneus nickname\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// "<nick> :Erroneus nickname"
}
// 433
void	err_nickname_inuse(int dest_fd, const std::string &nickname, const std::string &identifyer)
{
	std::string err_message = identifyer + nickname + " :Nickname is already in use\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// "<nick> :Nickname is already in use"
}
// 484
void	err_restricted(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + " :Your connection is restricted!\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// ":Your connection is restricted!"
}
// 491
void	err_nooperhost(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + ":No O-lines for your host\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}
// 464
void	err_passwd_mistmatch(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + ":Password incorrect\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}
// 501
void	err_umode_unknownflag(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + " :Unknown MODE flag\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 502
void	err_users_dontmatch(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + " :Cannot change mode for other users\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 473
void	err_invite_onlychan(int dest_fd, const std::string &channel, const std::string &identifyer)
{
	std::string err_message = identifyer + channel + " :Cannot join channel (+i)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 471
void	err_channel_isfull(int dest_fd, const std::string &channel, const std::string &identifyer)
{
	std::string err_message = identifyer + channel + " :Cannot join channel (+l)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 403
void	err_nosuch_channel(int dest_fd, const std::string &channel, const std::string &identifyer)
{
	std::string err_message = identifyer + channel + " :No such channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 407
void	err_toomany_targets(int dest_fd, const std::string &target, const std::string &identifyer)
{
	std::string err_message = identifyer + target + " :No such channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//replies


void	rpl_welcome_message(int dest_fd, const std::string &identifyer)
{
	std::string err_message = "Welcome to the Internet Relay Network " + identifyer + "\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

// 381
void	rpl_youreoper(int dest_fd, const std::string &identifyer)
{
	std::string err_message = identifyer + " :You are now an IRC operator\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

void	rpl_umodeis(int dest_fd, const std::string &user, const std::string &identifyer)
{
	std::string err_message = identifyer + user + " MODE string\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

