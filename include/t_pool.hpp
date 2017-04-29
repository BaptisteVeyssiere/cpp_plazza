//
// t_pool.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/src
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr 28 17:44:20 2017 Nathan Scutari
// Last update Sat Apr 29 17:30:06 2017 Nathan Scutari
//

#ifndef __T_POOL__
# define __T_POOL__

#include <list>
#include "Thread.hpp"
#include "command.hpp"
#include "data.hpp"
#include "CondVar.hpp"
#include "Mutex.hpp"

class T_pool
{
private:
  std::list<std::unique_ptr<Thread>>	threads;
  std::list<std::shared_ptr<t_data>>	d_list;
  std::list<std::shared_ptr<Mutex>>	mutex;
  std::list<std::shared_ptr<CondVar>>	condvar;

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
