//
// main.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/src
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:08:46 2017 Baptiste Veyssiere
// Last update Thu Apr 20 15:08:08 2017 Nathan Scutari
//

#include <iostream>
#include <regex>
#include <csignal>
#include "Parser.hpp"
#include "Process.hpp"
#define QUESTION	"Do you need something ? "

static void			main_loop(const int thread_nbr)
{
  Parser			parser;
  std::vector<t_command>	command_list;
  std::string			command;

  (void)thread_nbr;
  std::cout << QUESTION;
  while (getline(std::cin, command))
    {
      parser.parse(command, command_list);
      for (unsigned int i = 0; i < command_list.size(); i++)
	std::cout << "New command created :" << std::endl << "File: " << command_list[i].file << std::endl << "Information: " << command_list[i].information << std::endl;
      command.clear();
      command_list.clear();
      std::cout << QUESTION;
    }
}

int		main(int ac, char **av)
{
  int		thread_nbr;
  std::regex	pattern("^[0-9]+$");
  Process	p(2);

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
      if ((p.clone(42)))
	return (0);
      main_loop(thread_nbr);
    }
  catch (const std::exception &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      return (1);
    }
  return (0);
}
