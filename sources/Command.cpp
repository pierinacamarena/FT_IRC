#include "Command.hpp"

void	Command::set_rplnum(int rplnum)
{
	std::stringstream	ss;

	ss << rplnum;
	_rpl._rplnum = rplnum;
	add_arg(ss.str());
}

void	Command::add_dest(int dest)
{
	_rpl._dest.insert(dest);
}

void	Command::add_arg(const std::string& arg)
{
	_rpl._args.push_back(arg);
}

void	Command::pass(int fd, const std::vector<std::string>& params)
{
	add_arg(_data->get_srvname());
	add_dest(fd);
	if (_data->is_registered(fd))
		set_rplnum(ERR_ALREADYREGISTERED);
	else if (params.size() == 0)
		set_rplnum(ERR_NEEDMOREPARAMS);
	else if (!_data->compare_passwd(params[0]))
		set_rplnum(ERR_PASSWDMISMATCH);
	else
	{
		_data->set_user_state(fd, PASSWD_VALID);
		if (_data->is_registered(fd))
		{
			set_rplnum(RPL_WELCOME);
			add_arg(_data->get_user_info(fd));
		}
	}
}

void	Command::nick(int fd, const std::vector<std::string>& params)
{
	add_arg(_data->get_srvname());
	add_dest(fd);
	if (params.size() == 0)
		set_rplnum(ERR_NONICKNAMEGIVEN);
	else if (!valid_nickname(params[0]))
	{
		set_rplnum(ERR_ERRONEUSNICKNAME);
		add_arg(params[0]);
	}
	else if (_data->nickname_exists(params[0]))
	{
		set_rplnum(ERR_NICKNAMEINUSE);
		add_arg(params[0]);
	}
	else if (_data->check_user_flags(fd, RESTRICTED_UFLAG))
		set_rplnum(ERR_RESTRICTED);
	else
	{
		_data->add_nickname(fd, params[0]);
		_data->set_user_state(fd, NICK_VALID);
		if (_data->is_registered(fd))
		{
			set_rplnum(RPL_WELCOME);
			add_arg(_data->get_user_info(fd));
		}
	}
}

void	Command::user(int fd, const std::vector<std::string>& params)
{
	add_arg(_data->get_srvname());
	add_dest(fd);
	if (_data->is_registered(fd))
		set_rplnum(ERR_ALREADYREGISTERED);
	else if (params.size() < 4)
	{
		set_rplnum(ERR_NEEDMOREPARAMS);
		add_arg("USER");
	}
	else if (!valid_username(params[0]))
	{
		set_rplnum(ERR_ERRONEUSNICKNAME);
		add_arg(params[0]);
	}
	else
	{
		_data->add_username(fd, params[0]);
		if (params[1] == "4")
			_data->set_user_flags(fd, WALLOPS_UFLAG);
		else if (params[1] == "8")
			_data->set_user_flags(fd, INVISIBLE_UFLAG);
		_data->add_realname(fd, params[3]);
		_data->set_user_state(fd, USER_VALID);
		if (_data->is_registered(fd))
		{
			set_rplnum(RPL_WELCOME);
			add_arg(_data->get_user_info(fd));
		}
	}
}

void	Command::mode(int fd, const std::vector<std::string>& params)
{
	add_arg(_data->get_srvname());
	add_dest(fd);
	if (!_data->is_registered(fd))
		set_rplnum(ERR_NOTREGISTERED);
	else if (params.size() < 1)
		set_rplnum(ERR_NEEDMOREPARAMS);
	else if (params[0] != _data->get_nickname(fd))
		set_rplnum(ERR_USERSDONTMATCH);
	else if (params.size() == 1)
	{
		set_rplnum(RPL_UMODEIS);
		add_arg(mode_str(fd));
	}
	else if (!valid_mode(params[1]))
		set_rplnum(ERR_UMODEUNKNOWNFLAG);
	else
	{
		std::string::const_iterator	it = params[1].begin();
		int							flags = 0;
		bool						add = false;

		if (*it == '+')
			add = true;
		while (it != params[1].end())
		{
			switch (*it)
			{
				case 'i':
					flags |= INVISIBLE_UFLAG;
					break;
				case 'w':
					flags |= WALLOPS_UFLAG;
					break;
				case 'o':
					if (!add)
						flags |= OPER_UFLAG;
					break;
				case 'O':
					if (!add)
						flags |= LOCAL_OPER_UFLAG;
					break;
				case 'r':
					if (add)
						flags |= RESTRICTED_UFLAG;
					break;
			}
			it++;
		}
		if (add)
			_data->set_user_flags(fd, flags);
		else
			_data->unset_user_flags(fd, flags);
		set_rplnum(RPL_UMODEIS);
		add_arg(mode_str(fd));
	}
}

void	Command::quit(int fd, const std::vector<std::string>& params)
{
	add_arg(_data->get_srvname());
	add_dest(fd);
	set_rplnum(-1);
	if (params.size() > 0)
		add_arg(params[0]);
}

void	Command::join(int fd, const std::vector<std::string>& params)
{
	add_dest(fd);
	if (params.size() < 1)
	{
		add_arg(_data->get_srvname());
		set_rplnum(ERR_NEEDMOREPARAMS);
	}
}

// helper functions

std::string	Command::mode_str(int fd)
{
	std::string	ret;

	ret += _data->get_nickname(fd);
	ret += " ";
	ret += _data-> get_user_flags_str(fd);
	return (ret);
}

Command::Command(Data* data) : _data(data)
{
	// add commands to the command tree
	_cmd_map.insert(std::make_pair("PASS", &Command::pass));
	_cmd_map.insert(std::make_pair("NICK", &Command::nick));
	_cmd_map.insert(std::make_pair("USER", &Command::user));
	_cmd_map.insert(std::make_pair("MODE", &Command::mode));
	_cmd_map.insert(std::make_pair("QUIT", &Command::quit));
}

Reply	Command::out(void) const
{
	return (_rpl);
}

void	Command::reset(void) // to do after each call of 'execute_cmd'
{
	_rpl._rplnum = 0;
	_rpl._dest.clear();
	_rpl._args.clear();
}

void	Command::execute_cmd(int fd, const irc_cmd& cmd)
{
	std::map<std::string, FuncPtr>::iterator	it = _cmd_map.find(cmd._cmd);

	if (it != _cmd_map.end()) // found a valid command
		(this->*(it->second))(fd, cmd._params);	
	else
	{
		add_dest(fd);
		add_arg(cmd._cmd);
		set_rplnum(ERR_UNKNOWNCOMMAND);
	}
}
