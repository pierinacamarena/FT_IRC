#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <map>

#include "Data.hpp"
#include "cmd_structs.hpp"
#include "headers.hpp"
#include "parser.hpp"

class	Command {

	typedef void (Command::*FuncPtr)(int, const std::vector<std::string>&);

	private:
		
		Data*							_data;
		Reply							_rpl;
		std::map<std::string, FuncPtr>	_cmd_map;
		std::string						_srvname;
		std::string						_nickname;

		void	set_rplnum(int rplnum);
		void	add_dest(int dest);
		void	add_arg(const std::string& arg);

		void	pass(int fd, const std::vector<std::string>& params);
		void	nick(int fd, const std::vector<std::string>& params);
		void	user(int fd, const std::vector<std::string>& params);
		void	mode(int fd, const std::vector<std::string>& params);
		void	quit(int fd, const std::vector<std::string>& params);
		void	join(int fd, const std::vector<std::string>& params);

		// helper functions
		std::string	mode_str(int fd);

	public:

		Command(Data* data);

		Reply	out(void) const;
		void	reset(void); // to do after each call of 'execute_cmd'
		void	execute_cmd(int fd, const irc_cmd& cmd);
				
};

#endif
