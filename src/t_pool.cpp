//
// t_pool.cpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/src
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr 28 17:46:40 2017 Nathan Scutari
// Last update Fri Apr 28 18:26:10 2017 Nathan Scutari
//

#include "t_pool.hpp"

T_pool::T_pool(int t_nbr)
  : threads(), d_list()
{
  std::shared_ptr<t_data>	data;

  for (int i = 0 ; i < t_nbr ; ++i)
    {
      data = std::make_shared<t_data>();
      data->ready = 0;
      data->running = 0;
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
  for (std::list<std::shared_ptr<t_data>>::iterator it = d_list.begin() ; it != d_list.end() ; ++it)
    {
      if ((*it)->running == false)
	{
	  (*it)->running = 1;
	  (*it)->command = order;
	  (*it)->ready = 1;
	  return ;
	}
    }
}
