//
// Main_Process.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Apr 26 23:24:02 2017 Baptiste Veyssiere
// Last update Thu Apr 27 16:59:59 2017 Baptiste Veyssiere
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
}

void	Main_Process::Add_pipe()
{
  Named_pipe	pipe("/tmp/plazza" + std::to_string(this->process_nbr) + "_in",
		     "/tmp/plazza" + std::to_string(this->process_nbr) + "_out",
		     false);

  this->pipe_tab.push_back(pipe);
}

void	Main_Process::create_new_process()
{
  if (this->pattern.clone(this->process_nbr))
    exit(0);
  this->Add_pipe();
  ++this->process_nbr;
}

void	Main_Process::process_command(std::vector<t_command> &command_list)
{
  t_command	thread_request = { "", Information::PHONE_NUMBER, 1 };
  unsigned int	min;
  unsigned int	thread_it;

  for (std::vector<t_command>::iterator it = command_list.begin();
       it != command_list.end();
       it++)
    {
      min = this->thread_nbr * 2;
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
	  this->create_new_process();
	  this->pipe_tab[this->process_nbr - 1] << *it;
	}
    }
}
