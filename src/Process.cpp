//
// Process.cpp for Process in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:21:23 2017 Nathan Scutari
// Last update Thu Apr 20 15:07:17 2017 Nathan Scutari
//

#include <iostream>
#include <unistd.h>
#include "Process.hpp"

Process::Process(int thread_nbr)
  : t_nbr(thread_nbr)
{
  if (t_nbr < 1)
    throw std::exception();
}

int	Process::clone(int id)
{
  pid_t	pid;

  if ((pid = fork()) == -1)
    throw std::exception();
  else if (pid == 0)
    {
      id = id;
      //threads  (id)
      return (1);
    }
  return (0);
}

Process::~Process()
{}
