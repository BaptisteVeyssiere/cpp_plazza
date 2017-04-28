//
// Main_Process.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Apr 26 23:24:02 2017 Baptiste Veyssiere
// Last update Fri Apr 28 15:08:04 2017 Baptiste Veyssiere
//

#include "Main_Process.hpp"

Main_Process::Main_Process(unsigned int nbr)
  : pattern(nbr), thread_nbr(nbr), process_nbr(0), pipe_tab()
{
  this->create_new_process();
}

Main_Process::~Main_Process() {}

void	Main_Process::loop()
{
  Parser			parser;
  std::vector<t_command>	command_list;
  std::string			command;

  std::cout << QUESTION;
  while (getline(std::cin, command))
    {
      parser.parse(command, command_list);
      this->process_command(command_list);
      command.clear();
      command_list.clear();
      std::cout << QUESTION;
    }
  while (this->pipe_tab.size() > 0)
    this->check_processes();
}

void	Main_Process::Add_pipe(std::vector<Named_pipe>::iterator it, unsigned int id)
{
  Named_pipe	pipe("/tmp/plazza" + std::to_string(id) + "_in",
		     "/tmp/plazza" + std::to_string(id) + "_out",
		     false);

  this->pipe_tab.insert(it, pipe);
}

unsigned int	Main_Process::create_new_process()
{
  unsigned int				id;
  std::string				fifoname;
  std::vector<Named_pipe>::iterator	it;

  for (it = this->pipe_tab.begin(), id = 0;
       it != this->pipe_tab.end(); it++, id++)
    {
      fifoname = "/tmp/plazza" + std::to_string(id) + "_in";
      if (it->Get_pathin() != fifoname)
	break;
    }
  if (this->pattern.clone(id))
    exit(0);
  this->Add_pipe(it, id);
  ++this->process_nbr;
  return (id);
}

void	Main_Process::check_processes()
{
  t_command	check = { "", Information::PHONE_NUMBER, 0 };

  for (std::vector<Named_pipe>::iterator it = this->pipe_tab.begin();
       it != this->pipe_tab.end(); it++)
    {
      *it >> check;
      if (check.file == "end")
	{
	  it = this->pipe_tab.erase(it) - 1;
	  --this->process_nbr;
	}
      check.file = "";
    }
}

void	Main_Process::process_command(std::vector<t_command> &command_list)
{
  t_command	thread_request = { "", Information::PHONE_NUMBER, 1 };
  unsigned int	min;
  unsigned int	thread_it;
  unsigned int	id;

  for (std::vector<t_command>::iterator it = command_list.begin();
       it != command_list.end();
       it++)
    {

      min = this->thread_nbr * 2;
      this->check_processes();
      for (unsigned int i = 0; i < this->process_nbr; i++)
	{
	  thread_request.file = "";
	  thread_request.threads = 1;
	  this->pipe_tab[i] << thread_request;
	  while (thread_request.file != "ok")
	    this->pipe_tab[i] >> thread_request;
	  if (thread_request.threads < min)
	    {
	      min = thread_request.threads;
	      thread_it = i;
	    }
	}
      if (min < (this->thread_nbr * 2))
	this->pipe_tab[thread_it] << *it;
      else
	{
	  id = this->create_new_process();
	  this->pipe_tab[id] << *it;
	}
    }
}
