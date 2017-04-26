//
// Process.cpp for Process in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:21:23 2017 Nathan Scutari
// Last update Wed Apr 26 17:46:17 2017 Nathan Scutari
//

#include <iostream>
#include <unistd.h>
#include "Process.hpp"
#include "Thread.hpp"

Process::Process(int thread_nbr)
  : threads(), d_list(), t_nbr(thread_nbr)
{
  if (t_nbr < 1)
    throw std::exception();
}

int	Process::clone(int id)
{
  std::shared_ptr<t_data>	data;
  pid_t				pid;

  if ((pid = fork()) == -1)
    throw std::exception();
  else if (pid == 0)
    {
      id = id;
      data = std::make_shared<t_data>();
      data->ready = 0;
      data->running = 0;
      for (int i = 0 ; i < t_nbr ; ++i)
	{
	  d_list.push_back(data);
	  threads.push_back(std::make_unique<Thread>(d_list.back()));
	}
      //threads  (id)
      return (1);
    }
  return (0);
}

Process::~Process()
{}
