#ifndef _REPLY_HPP_
#define _REPLY_HPP_

#include "headers.hpp"

/*******************************ERRORS***********************************/
void	error_caller(int reply_id, const std::set<int>& dest_fds, const std::string &command, const std::string &identifyer);

void	err_unknown_command(int dest_fd, const std::string &command, const std::string &identifyer);
void	err_need_moreparams(int dest_fd, const std::string &command);
void	err_already_registered(int dest_fd, const std::string &identifyer);
void	err_not_registered(int dest_fd, const std::string &identifyer);
void	err_no_nicknamegive(int dest_fd, const std::string &identifyer);
void	err_erroneus_nickname(int dest_fd, const std::string &nickname, const std::string &identifyer);
void	err_nickname_inuse(int dest_fd, const std::string &nickname, const std::string &identifyer);
void	err_restricted(int dest_fd, const std::string &identifyer);
void	err_nooperhost(int dest_fd, const std::string &identifyer);
void	err_passwd_mistmatch(int dest_fd, const std::string &identifyer);
void	err_umode_unknownflag(int dest_fd, const std::string &identifyer);
void	err_users_dontmatch(int dest_fd, const std::string &identifyer);
void	err_invite_onlychan(int dest_fd, const std::string &channel, const std::string &identifyer);
void	err_channel_isfull(int dest_fd, const std::string &channel, const std::string &identifyer);
void	err_nosuch_channel(int dest_fd, const std::string &channel, const std::string &identifyer);
void	err_toomany_targets(int dest_fd, const std::string &target, const std::string &identifyer);

/******************************REPLIES***********************************/

void	reply_caller(int reply_id, const std::set<int> dest_fds, const std::string &identifyer);
void	rpl_welcome_message(int dest_fd, const std::string &identifyer);
void	rpl_youreoper(int dest_fd, const std::string &identifyer);


#endif
