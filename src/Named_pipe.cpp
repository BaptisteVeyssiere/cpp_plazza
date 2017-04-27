//
// Named_pipe.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Tue Apr 25 22:08:41 2017 Baptiste Veyssiere
// Last update Thu Apr 27 15:34:58 2017 Baptiste Veyssiere
//

#include <iostream>
#include <errno.h>
#include <cstring>
#include "Named_pipe.hpp"

Named_pipe::Named_pipe(const std::string &path_i, const std::string &path_o)
  : in(""), out(""), path_in(path_i), path_out(path_o)
{
  if (this->checkFifo(path_i) == false && mkfifo(path_i.c_str(), 0666) == -1)
    {
      std::cerr << "Error_in: " << std::strerror(errno) << " (" << path_i << ")" << std::endl;
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::exception();
    }
  if (this->checkFifo(path_o) == false && mkfifo(path_o.c_str(), 0666) == -1)
    {
      std::cerr << "Error out: " << std::strerror(errno) << " (" << path_o << ")" << std::endl;
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::exception();
    }
  this->path_in = path_i;
  this->path_out = path_o;
  this->in.close();
  this->out.close();
  this->open_in();
  this->open_out();
}

Named_pipe::Named_pipe(const Named_pipe &other)
  : in(""), out(""), path_in(other.path_in), path_out(other.path_out)
{
  this->in.close();
  this->out.close();
  this->open_in();
  this->open_out();
}

Named_pipe::~Named_pipe()
{
  if (this->in.is_open())
    this->in.close();
  if (this->out.is_open())
    this->out.close();
  if (this->checkFifo(this->path_in))
    std::remove(this->path_in.c_str());
  if (this->checkFifo(this->path_out))
    std::remove(this->path_out.c_str());
}

bool	Named_pipe::checkFifo(const std::string &file) const
{
  struct stat	statstruct;
  int		result;

  result = stat(file.c_str(), &statstruct);
  return (result == -1 ? false : true);
}

void	Named_pipe::open_in(void)
{
  this->in.open(this->path_in, std::ifstream::in);
  if (!this->in.is_open())
    {
      std::cerr << "In isn't open" << std::endl;
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::exception();
    }
}

void	Named_pipe::open_out(void)
{
  this->out.open(this->path_out, std::ofstream::out);
  if (!this->out.is_open())
    {
      std::cerr << "Out isn't open" << std::endl;
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::exception();
    }
}

void	Named_pipe::close_in(void)
{
  this->in.close();
}

void	Named_pipe::close_out(void)
{
  this->out.flush();
  this->out.close();
}

Named_pipe	&Named_pipe::operator<<(const t_command &command)
{
  this->out << command.file << " " << command.information << " " << command.threads << " ";
  return (*this);
}

Named_pipe		&Named_pipe::operator>>(t_command &command)
{
  int			info;
  std::stringstream	streamline;
  std::string		line;

  getline(this->in, line);
  if (this->in.gcount() > 0)
    {
      streamline << line;
      streamline >> command.file;
      streamline >> info;
      command.information = static_cast<Information>(info);
      streamline >> command.threads;
    }
  return (*this);
}
