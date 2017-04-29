//
// command.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/include
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:39:08 2017 Baptiste Veyssiere
// Last update Sat Apr 29 14:29:22 2017 Baptiste Veyssiere
//

#ifndef __COMMAND_HPP__
# define __COMMAND_HPP__

# include <vector>
# include <string>

enum	Information
  {
    PHONE_NUMBER,
    EMAIL_ADDRESS,
    IP_ADDRESS
  };

typedef struct			s_command
{
  std::string			file;
  Information			information;
  unsigned int			threads;
  std::vector<std::string>	data;
}				t_command;

#endif // !__COMMAND_HPP__
