//
// Process.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:11:25 2017 Nathan Scutari
// Last update Wed Apr 26 17:37:35 2017 Nathan Scutari
//

#ifndef __PROCESS_HPP__
# define __PROCESS_HPP__

#include <memory>
#include <list>
#include "command.hpp"
#include "Thread.hpp"
#include "data.hpp"

class Process
{
private:
  std::list<std::unique_ptr<Thread>>	threads;
  std::list<std::shared_ptr<t_data>>	d_list;
  int	t_nbr;

private:
  Process(Process &);
  Process	&operator=(Process &);
  Process();

public:
  Process(int);
  ~Process();

  int	clone(int);
};

#endif // !__PROCESS_HPP__
