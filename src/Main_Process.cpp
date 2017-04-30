//
// Main_Process.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Apr 26 23:24:02 2017 Baptiste Veyssiere
// Last update Sun Apr 30 03:59:33 2017 Baptiste Veyssiere
//

#include "Main_Process.hpp"

int	ok = 0;

Main_Process::Main_Process(unsigned int nbr)
  : pattern(nbr), thread_nbr(nbr), process_nbr(0), pipe_tab(), activated()
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
      while (this->process_nbr > 0)
	this->check_processes();
      std::for_each(this->pipe_tab.begin(), this->pipe_tab.end(),
		    [&](Named_pipe &fifo) { fifo.release(); });
    }
  catch (const std::exception &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      while (this->process_nbr > 0)
	this->check_processes();
      std::for_each(this->pipe_tab.begin(), this->pipe_tab.end(),
		    [&](Named_pipe &fifo) { fifo.release(); });
      return (1);
    }
  return (0);
}

void	Main_Process::Add_pipe(unsigned int id)
{
  Named_pipe	pipe("/tmp/plazza" + std::to_string(id) + "_in",
		     "/tmp/plazza" + std::to_string(id) + "_out",
		     false);

  if ((id + 1) < this->activated.size())
    this->activated[id] = true;
  else
    {
      this->activated.push_back(true);
      this->pipe_tab.push_back(pipe);
    }

}

unsigned int	Main_Process::create_new_process()
{
  unsigned int				id;
  std::string				fifoname;
  std::vector<Named_pipe>::iterator	it;

  id = 0;
  while (id < this->pipe_tab.size() && this->activated[id])
    ++id;
  if (this->pattern.clone(id))
    exit(0);
  this->Add_pipe(id);
  ++this->process_nbr;
  return (id);
}

void	Main_Process::remove_process(int i, const t_command &command)
{
  this->pipe_tab[i] << command;
  this->activated[i] = false;
  --this->process_nbr;
  std::cout << "Nbr of processes " << this->process_nbr << std::endl;
}

void	Main_Process::display_result(const t_command &command) const
{
  std::vector<std::string>	info { "PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS" };

  std::cout << command.file << " " << info[command.information] << ":" << std::endl;
  std::for_each(command.data.begin(), command.data.end(), [&](const std::string &str) { std::cout << str << std::endl; });
  ++ok;
  std::cout << ok << " commands received" << std::endl;
}

void	Main_Process::check_processes()
{
  t_command			check = { "", Information::PHONE_NUMBER, 0, {} };

  for (int i = 0; i < static_cast<int>(this->pipe_tab.size()); i++)
    {
      if (this->activated[i] == false)
	continue;
      this->pipe_tab[i] >> check;
      if (check.file == "end")
	this->remove_process(i, check);
      else if (check.data.size() > 0 || check.file != "")
	this->display_result(check);
      check.file = "";
      check.data.clear();
    }
}

void	Main_Process::process_command(std::vector<t_command> &command_list)
{
  t_command	thread_request = { "", Information::PHONE_NUMBER, 1, {} };
  unsigned int	min;
  unsigned int	thread_it;
  unsigned int	id;
  std::vector<std::string>	info { "PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS" };

  for (unsigned int it = 0; it < command_list.size(); it++)
    {
      min = this->thread_nbr * 2;
      this->check_processes();
      for (int i = 0; i < static_cast<int>(this->process_nbr); i++)
	{
	  if (this->activated[i] == false)
	    continue;
	  thread_request.file = "";
	  thread_request.threads = 1;
	  thread_request.data.clear();
	  this->pipe_tab[i] << thread_request;
	  while (thread_request.file != "ok" && thread_request.file != "end")
	    {
	      if (thread_request.file != "")
		this->display_result(thread_request);
	      thread_request.file = "";
	      this->pipe_tab[i] >> thread_request;
	    }
	  if (thread_request.file == "end")
	    this->remove_process(i, thread_request);
	  else if (thread_request.threads < min)
	    {
	      min = thread_request.threads;
	      thread_it = i;
	    }
	}
      if (min < (this->thread_nbr * 2))
	this->pipe_tab[thread_it] << command_list[it];
      else
	{
	  id = this->create_new_process();
	  this->pipe_tab[id] << command_list[it];
	}
    }
}
