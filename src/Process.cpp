//
// Process.cpp for Process in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:21:23 2017 Nathan Scutari
// Last update Thu Apr 27 16:57:31 2017 Nathan Scutari
//

#include <iostream>
#include <unistd.h>
#include "Process.hpp"
#include "Thread.hpp"

Process::Process(int thread_nbr)
  : threads(), d_list(), orders(), t_nbr(thread_nbr), pipe(NULL), time_c(0), timer(0)
{
  if (t_nbr < 1)
    throw std::exception();
}

t_command	Process::order_nbr()
{
  t_command	order = { "ok", Information::PHONE_NUMBER, 0 };

  order.threads = static_cast<unsigned int>(orders.size());
  for (std::list<std::shared_ptr<t_data>>::iterator it = d_list.begin() ; it != d_list.end() ; ++it)
    {
      if ((*it)->running == true)
	++order.threads;
    }
  return (order);
}

void	Process::assign_order(t_command order)
{
  for (std::list<std::shared_ptr<t_data>>::iterator it = d_list.begin() ; it != d_list.end() ; ++it)
    {
      if ((*it)->running == false)
	{
	  (*it)->running = 1;
	  (*it)->command = order;
	  (*it)->ready = 1;
	}
    }
}

int	Process::orders_to_threads()
{
  int		threads_running(0);

  for (int i = 0 ; i < t_nbr ; ++i)
    ++threads_running;
  if (threads_running == t_nbr)
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

void	Process::thread_control(void)
{
  t_data	data;
  t_command	order = { "", Information::PHONE_NUMBER, 0 };

  *pipe >> order;
  if (order.file == "" && order.threads == 1)
    *pipe << order_nbr();
  else if (order.file != "" && order.threads == 0)
    orders.push_back(order);
  else if (orders_to_threads())
    return ;
}

int	Process::clone(int id)
{
  std::shared_ptr<t_data>	data;
  pid_t				pid;

  if ((pid = fork()) == -1)
    throw std::exception();
  else if (pid == 0)
    {
      std::cout << "o" << std::endl;
      pipe = new Named_pipe("/tmp/plazza_" + std::to_string(id) + "_out", "/tmp/plazza_" + std::to_string(id) + "_in", true);
      std::cout << "k" << std::endl;
      data = std::make_shared<t_data>();
      data->ready = 0;
      data->running = 0;
      for (int i = 0 ; i < t_nbr ; ++i)
	{
	  d_list.push_back(data);
	  threads.push_back(std::make_unique<Thread>(d_list.back()));
	}
      thread_control();
      return (1);
    }
  return (0);
}

Process::~Process()
{
  if (pipe)
    delete pipe;
}
