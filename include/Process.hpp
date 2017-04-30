//
// Process.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:11:25 2017 Nathan Scutari
// Last update Sun Apr 30 15:20:11 2017 Nathan Scutari
//

#ifndef __PROCESS_HPP__
# define __PROCESS_HPP__

#include <memory>
#include <ctime>
#include <list>
#include "t_pool.hpp"
#include "command.hpp"
#include "Thread.hpp"
#include "data.hpp"
#include "Named_pipe.hpp"

class Process
{
private:
  T_pool				*pool;
  std::list<t_command>			orders;
  int					t_nbr;
  Named_pipe				*pipe;
  time_t				time_c;
  int					timer;

private:
  Process(Process &);
  Process	&operator=(Process &);

  void		thread_control(int);
  t_command	order_nbr();
  int		orders_to_threads();
  void		assign_order(t_command);

public:
  Process(int);
  ~Process();

  pid_t	clone(int);
};

#endif // !__PROCESS_HPP__
