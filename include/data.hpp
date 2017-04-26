//
// data.hpp for data in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 26 17:14:58 2017 Nathan Scutari
// Last update Wed Apr 26 17:46:42 2017 Nathan Scutari
//

#ifndef __DATA_HPP__
# define __DATA_HPP__

#include "command.hpp"

typedef struct	s_data
{
  bool		ready = false;
  bool		running = false;
  t_command	command = { "", Information::PHONE_NUMBER, 0 };
}		t_data;

#endif // __DATA_HPP__
