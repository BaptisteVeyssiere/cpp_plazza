//
// main.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/src
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:08:46 2017 Baptiste Veyssiere
// Last update Thu Apr 27 00:13:50 2017 Baptiste Veyssiere
//

#include <iostream>
#include <regex>
#include <csignal>
#include "Main_Process.hpp"

static void	init(unsigned int thread_nbr)
{
  Main_Process	main_process(thread_nbr);

  main_process.loop();
}

int		main(int ac, char **av)
{
  int		thread_nbr;
  std::regex	pattern("^[0-9]+$");

  std::signal(SIGINT, SIG_IGN);
  std::signal(SIGTERM, SIG_IGN);
  try
    {
      if (ac < 2 || ac > 2 || !(std::regex_match(av[1], pattern)) ||
	  (thread_nbr = std::stoi(av[1])) < 1)
	{
	  std::cerr << "Usage: ./plazza nbr_of_thread" << std::endl;
	  return (1);
	}
      init(thread_nbr);
    }
  catch (const std::exception &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      return (1);
    }
  return (0);
}
