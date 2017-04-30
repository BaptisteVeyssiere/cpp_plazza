//
// Process.cpp for Process in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:21:23 2017 Nathan Scutari
// Last update Sun Apr 30 16:36:02 2017 Nathan Scutari
//

#include <iostream>
#include <unistd.h>
#include "Process.hpp"
#include "Thread.hpp"
#include "t_pool.hpp"

Process::Process(int thread_nbr)
  : pool(NULL), orders(), t_nbr(thread_nbr), pipe(NULL), time_c(0), timer(0)
{
  if (t_nbr < 1)
    throw std::exception();
}

t_command	Process::order_nbr()
{
  t_command	order = { "ok", Information::PHONE_NUMBER, 0, {} };

  order.threads = static_cast<unsigned int>(orders.size());
  order.threads += pool->getRunningThreadsNbr();
  return (order);
}

void	Process::assign_order(t_command order)
{
  pool->sendOrderToThread(order);
}

int	Process::orders_to_threads()
{
  int		threads_running(0);

  threads_running = pool->getRunningThreadsNbr();
  if (threads_running >= t_nbr)
    return (0);
  else if (orders.size() > 0)
    {
      timer = 0;
      while (threads_running < t_nbr && orders.size() > 0)
	{
	  assign_order(orders.front());
	  orders.pop_front();
	  ++threads_running;
	}
    }
  else if (threads_running == 0)
    {
      if (timer == 0)
	{
	  timer = 1;
	  time_c = time(NULL);
	}
      if (time(NULL) - time_c >= 5)
	return (1);
    }
  return (0);
}

void	Process::thread_control(int id)
{
  t_data			data;
  t_command			order = { "", Information::PHONE_NUMBER, 0, {} };

  while (1)
    {
      order.file = "";
      order.threads = 0;
      order.data.clear();
      *pipe >> order;
      if (order.file == "" && order.threads == 1)
	  *pipe << order_nbr();
      else if (order.file != "" && order.threads == 0)
	  orders.push_back(order);
      else if (orders_to_threads())
	{
	  std::cout << "Timeout: Process with id: " << id << std::endl;
	  order.file = "end";
	  order.threads = id;
	  *pipe << order;
	  order.file = "";
	  while (1)
	    {
	      *pipe >> order;
	      if (order.file == "end")
		return ;
	    }
	}
      if (pool->getFinishedOrder(order))
	*pipe << order;
    }
}

pid_t	Process::clone(int id)
{
  pid_t				pid;

  if ((pid = fork()) == -1)
    throw std::exception();
  else if (pid == 0)
    {
      pipe = new Named_pipe("/tmp/plazza" + std::to_string(id) + "_out", "/tmp/plazza" + std::to_string(id) + "_in", true);
      pool = new T_pool(t_nbr);
      thread_control(id);
      return (0);
    }
  return (pid);
}

Process::~Process()
{
  if (pipe)
    delete pipe;
  std::cout << "Delete Process" << std::endl;
}
