/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:59:07 by pcamaren          #+#    #+#             */
/*   Updated: 2023/03/07 17:27:23 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Reply.hpp"
void	error_caller(int reply_id, const std::set<int>& dest_fds, const std::vector<std::string>& args)
{
	std::set<int>::const_iterator it = dest_fds.begin();
	switch (reply_id)
	{
	case ERR_UNKNOWNCOMMAND:
		for (; it != dest_fds.end(); ++it)
			err_unknown_command(*it, args);
		break;
	case ERR_NONICKNAMEGIVEN:
		for (; it != dest_fds.end(); ++it)
			err_no_nicknamegive(*it, args);
		break;
	case ERR_ERRONEUSNICKNAME:
		for (; it != dest_fds.end(); ++it)
			err_erroneus_nickname(*it, args);
		break;
	case ERR_NICKNAMEINUSE:
		for (; it != dest_fds.end(); ++it)
			err_nickname_inuse(*it, args);
		break;
	case ERR_NOTREGISTERED:
		for (; it != dest_fds.end(); ++it)
			err_not_registered(*it, args);
		break;
	case ERR_NEEDMOREPARAMS:
		for (; it != dest_fds.end(); ++it)
			err_need_moreparams(*it, args);
		break;
	case ERR_ALREADYREGISTERED: 
		for (; it != dest_fds.end(); ++it)
			err_already_registered(*it, args);
		break;
	case ERR_PASSWDMISMATCH: 
		for (; it != dest_fds.end(); ++it)
			err_passwd_mistmatch(*it, args);
		break;
	case ERR_RESTRICTED:
		for (; it != dest_fds.end(); ++it)
			err_restricted(*it, args);
		break;
	case ERR_USERSDONTMATCH:
		for (; it != dest_fds.end(); ++it)
			err_users_dontmatch(*it, args);
	case ERR_UMODEUNKNOWNFLAG:
		for (; it != dest_fds.end(); ++it)
			err_umode_unknownflag(*it, args);
	case ERR_INVITEONLYCHAN:
		for (; it != dest_fds.end(); ++it)
			err_invite_onlychan(*it, args);
	case ERR_CHANNELISFULL:
		for (; it != dest_fds.end(); ++it)
			err_channel_isfull(*it, args);
	case ERR_NOSUCHCHANNEL:
		for (; it != dest_fds.end(); ++it)
			err_nosuch_channel(*it, args);
	case ERR_TOOMANYTARGETS:
		for (; it != dest_fds.end(); ++it)
			err_toomany_targets(*it, args);		
	case RPL_WELCOME:
		for (; it != dest_fds.end(); ++it)
			rpl_welcome_message(*it, args);
		break;
	case RPL_UMODEIS:
		for (; it != dest_fds.end(); ++it)
			rpl_umodeis(*it, args);
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
void	err_unknown_command(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " " + args[2] + " :Unknown command\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

//461
void	err_need_moreparams(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Not enough parameters\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

//462
void	err_already_registered(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :Unauthorized command (already registered)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// ":Unauthorized command (alredy registered)"
}

//451
void	err_not_registered(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :You have not registered\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

//431
void	err_no_nicknamegive(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :No nickname given\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// ":No nickname given"
}

// 432 HERE I NEED TO CHECK IF HE IS STORING THE ERRONEOUS NICKNAME
void	err_erroneus_nickname(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Erroneus nickname\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}
// 433
void	err_nickname_inuse(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :Nickname is already in use\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// "<nick> :Nickname is already in use"
}
// 484
void	err_restricted(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :Your connection is restricted!\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
	// ":Your connection is restricted!"
}
// 464
void	err_passwd_mistmatch(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + ":Password incorrect\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}
// 501
void	err_umode_unknownflag(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :Unknown MODE flag\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 502
void	err_users_dontmatch(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + ":Cannot change mode for other users\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 473
void	err_invite_onlychan(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Cannot join channel (+i)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 471
void	err_channel_isfull(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Cannot join channel (+l)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 403
void	err_nosuch_channel(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :No such channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 407
void	err_toomany_targets(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :" + args[0] + "recipients." + args[3] + "\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 474
void	err_banned_fromchan(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Cannot join channel (+b)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
// 475
void	err_badchannel_key(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Cannot join channel (+k)\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//476
void	err_bad_chanmask(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Bad Channel Mask\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//405
void	err_toomany_channels(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :You have joined too many channels\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//437
void	err_unavail_resource(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Nick/channel is temporarily unavailable\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//442
void	err_noton_channel(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :You're not on that channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//477
void	err_nochan_modes(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Channel doesn't support modes\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//441
void	err_usernot_inchannel(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[1] + " " + args[2] + " :They aren't on that channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//467
void	err_keyset(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Channel key already set\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//482
void	err_chano_privsneeded(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :You're not channel operator\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//472
void	err_unknown_mode(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :is unknown mode char to me for " + args[3] + "\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//402
void	err_nosuch_server(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[0] + " :No such server\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//401
void	err_nosuch_nick(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[1] + " :No such nick/channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//443
void	err_user_on_channel(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[1] + " " + args[2] + " :is already on channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//411
void	err_norecipient(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :No recipient given (" + args[2] + ")\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//404
void	err_cannotsend_tochan(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Cannot send to channel\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//414
void	err_wildto_plevel(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :Wildcard in toplevel domain\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//412
void	err_notext_tosend(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :No text to send\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//413
void	err_noto_plevel(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :No toplevel domain specified\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//406
void	err_wasno_suchnick(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + " :There was no such nickname\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//481
void	err_noprivileges(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :Permission Denied- You're not an IRC operator\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//483
void	err_cant_killserver(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :You can't kill a server!\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//409
void	err_noorigin(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :No origin specified\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//446
void	err_users_disabled(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :USERS has been disabled\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//424
void	err_filerror(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :File error doing " + args[2] + "on" + args[3] + "\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);	
}
//replies


void	rpl_welcome_message(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + "Welcome to the Internet Relay Network, " + args[1] + "\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

// 381
void	rpl_youreoper(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + " :You are now an IRC operator\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

void	rpl_umodeis(int dest_fd, const std::vector<std::string> args)
{
	std::string	prefix = ":" + args[0] + " " + args[1];
	std::string err_message = prefix + args[2] + "\n";
	send(dest_fd, err_message.c_str(), err_message.size(), 0);
}

