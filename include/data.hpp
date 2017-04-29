//
// data.hpp for data in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 26 17:14:58 2017 Nathan Scutari
// Last update Sat Apr 29 17:17:49 2017 Nathan Scutari
//

#ifndef __DATA_HPP__
# define __DATA_HPP__

#include <atomic>
#include "command.hpp"

typedef struct	s_data
{
  std::atomic<int>	ready;
  std::atomic<int>	running;
  t_command	command = { "", Information::PHONE_NUMBER, 0, {} };
  std::string		result = "";

  s_data()
    : ready(false), running(false)
  {}
}		t_data;

#endif // __DATA_HPP__
