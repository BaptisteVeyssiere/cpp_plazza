//
// Main_Process.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 27 00:21:57 2017 Baptiste Veyssiere
// Last update Thu Apr 27 00:32:56 2017 Baptiste Veyssiere
//

#ifndef __MAIN_PROCESS_HPP__
# define __MAIN_PROCESS_HPP__

# include <iostream>
# include <unistd.h>
# include "Named_pipe.hpp"
# include "Parser.hpp"
# include "Process.hpp"

# define QUESTION "Welcome ! What do you need ? "

class	Main_Process
{
private:
  Process			pattern;
  unsigned int			thread_nbr;
  unsigned int			process_nbr;
  std::vector<Named_pipe>	pipe_tab;

private:
  Main_Process(const Main_Process &);
  Main_Process();
  Main_Process	&operator=(const Main_Process &);

public:
  Main_Process(unsigned int);
  virtual ~Main_Process();
  void	loop();

private:
  void	Add_pipe();
  void	create_new_process();
  void	process_command(std::vector<t_command> &);
};

#endif // !__MAIN_PROCESS_HPP__
