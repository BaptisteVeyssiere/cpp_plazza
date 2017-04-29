//
// data.hpp for data in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 26 17:14:58 2017 Nathan Scutari
// Last update Sat Apr 29 18:06:31 2017 Nathan Scutari
//

#ifndef __DATA_HPP__
# define __DATA_HPP__

#include <atomic>
#include "command.hpp"
#include "CondVar.hpp"

typedef struct	s_data
{
  std::atomic<int>	ready;
  std::atomic<int>	running;
  std::atomic<int>	end;
  t_command	command = { "", Information::PHONE_NUMBER, 0, {} };
  std::vector<std::string>	result;

  s_data()
    : ready(false), running(false), end(false), result()
  {}
}		t_data;

#endif // __DATA_HPP__
