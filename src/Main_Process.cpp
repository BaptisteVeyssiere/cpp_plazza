//
// Main_Process.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Apr 26 23:24:02 2017 Baptiste Veyssiere
// Last update Sat Apr 29 20:34:40 2017 Baptiste Veyssiere
//

#include "Main_Process.hpp"

Main_Process::Main_Process(unsigned int nbr)
  : pattern(nbr), thread_nbr(nbr), process_nbr(0), pipe_tab()
{
  this->create_new_process();
}

Main_Process::~Main_Process() {}

int	Main_Process::loop()
{
  Parser			parser;
  std::vector<t_command>	command_list;
  std::string			command;
  std::streambuf		*pbuf;
  std::streamsize		size;

  std::cout << QUESTION;
  std::cin.sync_with_stdio(false);
  try
    {
      while (this->process_nbr > 0)
	{
	  pbuf = std::cin.rdbuf();
	  size = pbuf->in_avail();
	  if (size > 0)
	    {
	      if (getline(std::cin, command))
		{
		  parser.parse(command, command_list);
		  this->process_command(command_list);
		  command.clear();
		  command_list.clear();
		  std::cout << QUESTION;
		}
	      else
		break;
	    }
	  this->check_processes();
	}
      while (this->pipe_tab.size() > 0)
	this->check_processes();
    }
  catch (const std::exception &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      while (this->process_nbr > 0)
	this->check_processes();
      return (1);
    }
  return (0);
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
  t_command			check = { "", Information::PHONE_NUMBER, 0, {} };
  std::vector<std::string>	info { "PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS" };
  static int			ok = 0;

  for (std::vector<Named_pipe>::iterator it = this->pipe_tab.begin();
       it != this->pipe_tab.end(); ++it)
    {
      *it >> check;
      if (check.file == "end")
	{
	  it->release();
	  it = this->pipe_tab.erase(it);
	  --this->process_nbr;
	  if (this->pipe_tab.size() == 0)
	    break;
	}
      else if (check.data.size() > 0 || check.file != "")
	{
	  std::cout << check.file << " " << info[check.information] << ":" << std::endl;
	  std::for_each(check.data.begin(), check.data.end(), [&](const std::string &str) { std::cout << str << std::endl; });
	  ++ok;
	  std::cout << ok << " commands received" << std::endl;
	}
      check.file = "";
    }
}

void	Main_Process::process_command(std::vector<t_command> &command_list)
{
  t_command	thread_request = { "", Information::PHONE_NUMBER, 1, {} };
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
	    {
	      this->pipe_tab[i] >> thread_request;
	      std::cout << "Nbr of threads active: " << this->process_nbr << std::endl;
	    }
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
