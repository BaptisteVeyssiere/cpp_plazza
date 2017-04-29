//
// t_pool.cpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/src
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr 28 17:46:40 2017 Nathan Scutari
// Last update Sat Apr 29 17:04:36 2017 Nathan Scutari
//

#include "t_pool.hpp"

T_pool::T_pool(int t_nbr)
  : threads(), d_list(), mutex(), condvar()
{
  std::shared_ptr<t_data>	data;
  std::shared_ptr<CondVar>	cvar;
  std::shared_ptr<Mutex>	mut;

  for (int i = 0 ; i < t_nbr ; ++i)
    {
      data = std::make_shared<t_data>();
      data->ready = 0;
      data->running = 0;
      mut = std::make_shared<Mutex>();
      cvar = std::make_shared<CondVar>(*mut);
      d_list.push_back(data);
      threads.push_back(std::make_unique<Thread>(d_list.back()));
    }
}

T_pool::~T_pool()
{}

int	T_pool::getRunningThreadsNbr()
{
  int	nbr;

  nbr = 0;
  for (std::list<std::shared_ptr<t_data>>::iterator it = d_list.begin() ; it != d_list.end() ; ++it)
    {
      if ((*it)->running == true)
	++nbr;
    }
  return (nbr);
}

void	T_pool::sendOrderToThread(t_command &order)
{
  int	pos = 0;
  for (std::list<std::shared_ptr<t_data>>::iterator it = d_list.begin() ; it != d_list.end() ; ++it)
    {
      if ((*it)->running == false)
	{
	  (*it)->running = 1;
	  (*it)->command = order;
	  (*it)->ready = 1;
	  std::list<std::shared_ptr<CondVar>>::iterator cit = next(std::next(condvar.begin(), pos));
	  (*cit)->notify_all();
	  return ;
	}
      ++pos;
    }
}
