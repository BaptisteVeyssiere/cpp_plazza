//
// t_pool.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/src
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr 28 17:44:20 2017 Nathan Scutari
// Last update Fri Apr 28 18:26:16 2017 Nathan Scutari
//

#ifndef __T_POOL__
# define __T_POOL__

#include <list>
#include "Thread.hpp"
#include "command.hpp"
#include "data.hpp"

class T_pool
{
private:
  std::list<std::unique_ptr<Thread>>	threads;
  std::list<std::shared_ptr<t_data>>	d_list;

private:
  T_pool(T_pool &);
  T_pool	&operator=(T_pool &);

public:
  T_pool(int);
  ~T_pool();

public:
  int	getRunningThreadsNbr();
  void	sendOrderToThread(t_command &);
};

#endif // !__T_POOL__
