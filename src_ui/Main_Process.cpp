//
// Main_Process.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Wed Apr 26 23:24:02 2017 Baptiste Veyssiere
// Last update Sun Apr 30 22:04:30 2017 Baptiste Veyssiere
//

#include "Main_Process_ui.hpp"

Main_Process::Main_Process(unsigned int nbr)
  : pattern(nbr), thread_nbr(nbr), process_nbr(0), pipe_tab(), activated(), pid(), log_file(), interface(NULL)
{
  this->interface = new Ui(nbr);
  this->create_new_process();
  this->log_file.open("logs.txt");
}

Main_Process::~Main_Process()
{
  delete this->interface;
  if (this->log_file.is_open())
    this->log_file.close();
}

void	Main_Process::wait_process()
{
  int	status;

  while (this->process_nbr > 0)
    this->check_processes();
  while (this->pid.size() > 0)
    if (waitpid(this->pid[0], &status, WNOHANG))
      this->pid.erase(this->pid.begin());
  std::for_each(this->pipe_tab.begin(), this->pipe_tab.end(),
		[&](Named_pipe &fifo) { fifo.release(); });
}

int	Main_Process::loop()
{
  Parser			parser;
  std::vector<t_command>	command_list;
  std::string			command;
  std::streambuf		*pbuf;
  std::streamsize		size;
  std::string			str;

  std::cin.sync_with_stdio(false);
  str = "";
  try
    {
      pbuf = std::cin.rdbuf();
      size = pbuf->in_avail();
      while (size > 0)
	{
	  if (getline(std::cin, command))
	    {
	      parser.parse(command, command_list);
	      this->process_command(command_list);
	      if ((str = this->interface->refresh()) == "exit")
	      	break;
	      command.clear();
	      command_list.clear();
	      this->check_processes();
	    }
	  pbuf = std::cin.rdbuf();
	  size = pbuf->in_avail();
	}
      while (str != "exit")
	{
	  if ((command = this->interface->refresh()) == "exit")
	    break;
	  else if (command != "")
	    {
	      command_list.clear();
	      parser.parse(command, command_list);
	      this->process_command(command_list);
	      command.clear();
	      this->check_processes();
	    }
	  this->check_processes();
	}
      this->wait_process();
    }
  catch (const std::exception &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl;
      this->wait_process();
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
  pid_t					ret;

  id = 0;
  while (id < this->pipe_tab.size() && this->activated[id])
    ++id;
  if ((ret = this->pattern.clone(id)) == 0)
    exit(0);
  this->Add_pipe(id);
  ++this->process_nbr;
  this->pid.push_back(ret);
  return (id);
}

void	Main_Process::remove_process(int i, const t_command &command)
{
  this->pipe_tab[i] << command;
  this->activated[i] = false;
  --this->process_nbr;
}

void	Main_Process::display_result(const t_command &command)
{
  std::vector<std::string>	info { "PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS" };

  if (!this->log_file.is_open())
    throw std::runtime_error("The log file is not open");
  this->log_file << command.file << " " << info[command.information] << ":" << std::endl;
  std::for_each(command.data.begin(), command.data.end(), [&](const std::string &str) { this->log_file << str << std::endl; });
  this->interface->addOrder(command);
}

void			Main_Process::check_processes()
{
  t_command		check = { "", Information::PHONE_NUMBER, 0, {} };

  for (int i = 0; i < static_cast<int>(this->pipe_tab.size()); i++)
    {
      if (this->activated[i] == false)
	continue;
      this->pipe_tab[i] >> check;
      if (check.file == "end")
	this->remove_process(i, check);
      else if (check.file != "")
	this->display_result(check);
      check.file = "";
      check.data.clear();
    }
}

void		Main_Process::process_command(std::vector<t_command> &command_list)
{
  t_command	thread_request = { "", Information::PHONE_NUMBER, 1, {} };
  unsigned int	min;
  unsigned int	thread_it;
  unsigned int	id;
  std::vector<int>	ids;
  std::vector<int>	nbr;
  std::string	str;

  for (unsigned int it = 0; it < command_list.size(); it++)
    {
      min = this->thread_nbr * 2;
      this->check_processes();
      for (int i = 0; i < static_cast<int>(this->process_nbr); i++)
	{
	  if (this->activated[i])
	    {
	      thread_request = { "", Information::PHONE_NUMBER, 1, {} };
	      this->pipe_tab[i] << thread_request;
	      while (thread_request.file != "ok" && thread_request.file != "end")
		{
		  if (thread_request.file != "")
		    this->display_result(thread_request);
		  this->pipe_tab[i] >> thread_request;
		}
	      if (thread_request.file == "end")
		this->remove_process(i, thread_request);
	      else
		{
		  nbr.push_back(thread_request.threads);
		  str = this->pipe_tab[i].Get_pathin();
		  str = str.substr(11);
		  str = str.substr(0, str.size() - 3);
		  ids.push_back(std::stoi(str));
		  if (thread_request.threads < min)
		    {
		      min = thread_request.threads;
		      thread_it = i;
		    }
		}
	    }
	}
      this->interface->updateStatus(nbr, ids);
      if (min < (this->thread_nbr * 2))
	this->pipe_tab[thread_it] << command_list[it];
      else
	{
	  id = this->create_new_process();
	  this->pipe_tab[id] << command_list[it];
	}
    }
}
