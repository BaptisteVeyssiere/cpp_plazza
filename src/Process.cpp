//
// Process.cpp for Process in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:21:23 2017 Nathan Scutari
// Last update Wed Apr 19 11:53:18 2017 Nathan Scutari
//

#include <iostream>
#include <unistd.h>
#include "Process.hpp"

Process::Process(int thread_nbr, int id_arg)
  : t_nbr(thread_nbr), id(id_arg)
{
  pid_t	pid;

  if ((pid = fork()) == -1)
    throw std::exception();
  else if (pid == 0)
    {
      // create threads
    }
}

int	Process::is_full()
{
  int	i;

  i = -1;
  while (++i < t_nbr)
    {

    }
  return (0);
}

Process::~Process()
{

}
