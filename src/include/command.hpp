//
// command.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/include
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:39:08 2017 Baptiste Veyssiere
// Last update Wed Apr 26 17:09:31 2017 Nathan Scutari
//

#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

enum	Information
  {
    PHONE_NUMBER,
    EMAIL_ADDRESS,
    IP_ADDRESS
  };

typedef struct	s_command
{
  std::string	file;
  Information	information;
  unsigned int	threads;
}		t_command;

#endif // !__COMMAND_HPP__
