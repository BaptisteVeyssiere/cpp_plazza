//
// main.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/src
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:08:46 2017 Baptiste Veyssiere
// Last update Sun Apr 30 20:46:35 2017 Baptiste Veyssiere
//

#include <iostream>
#include <regex>
#include <csignal>
#include "Main_Process.hpp"

static int	init(unsigned int thread_nbr)
{
  Main_Process	main_process(thread_nbr);

  return (main_process.loop());
}

int		main(int ac, char **av, char **env)
{
  int		thread_nbr;
  std::regex	pattern("^[0-9]+$");

  std::signal(SIGINT, SIG_IGN);
  std::signal(SIGTERM, SIG_IGN);
  if (ac < 2 || ac > 2 || !(std::regex_match(av[1], pattern)) ||
      (thread_nbr = std::stoi(av[1])) < 1 || env == NULL || env[0] == NULL)
    {
      std::cerr << "Usage: ./plazza nbr_of_thread" << std::endl;
      return (1);
    }
  try
    {
      return (init(thread_nbr));
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }
}
