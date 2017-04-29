//
// Named_pipe.cpp for Project-Master in /home/veyssi_b/test/plazza
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Tue Apr 25 22:08:41 2017 Baptiste Veyssiere
// Last update Sat Apr 29 14:52:21 2017 Baptiste Veyssiere
//

#include <iostream>
#include <errno.h>
#include <cstring>
#include "Named_pipe.hpp"

Named_pipe::Named_pipe(const std::string &path_i, const std::string &path_o, bool order)
  : in(""), out(""), path_in(path_i), path_out(path_o)
{
  if (this->checkFifo(path_i) == false && mkfifo(path_i.c_str(), 0666) == -1)
    {
      std::cerr << "Error_in: " << std::strerror(errno) << " (" << path_i << ")" << std::endl;
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::runtime_error("Error in the creation of " + path_i);
    }
  if (this->checkFifo(path_o) == false && mkfifo(path_o.c_str(), 0666) == -1)
    {
      std::cerr << "Error out: " << std::strerror(errno) << " (" << path_o << ")" << std::endl;
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::runtime_error("Error in the creation of " + path_o);
    }
  this->path_in = path_i;
  this->path_out = path_o;
  this->in.close();
  this->out.close();
  if (order == true)
    this->open_in();
  this->open_out();
  if (order == false)
    this->open_in();
}

Named_pipe::Named_pipe(const Named_pipe &other)
  : in(""), out(""), path_in(other.path_in), path_out(other.path_out)
{
  this->in.close();
  this->out.close();
  this->open_in();
  this->open_out();
}

Named_pipe	&Named_pipe::operator=(const Named_pipe &other)
{
  this->path_in = other.path_in;
  this->path_out = other.path_out;
  this->open_in();
  this->open_out();
  return (*this);
}

void	Named_pipe::release()
{
  if (this->checkFifo(this->path_in))
    std::remove(this->path_in.c_str());
  if (this->checkFifo(this->path_out))
    std::remove(this->path_out.c_str());
}

Named_pipe::~Named_pipe()
{
  if (this->in.is_open())
    this->in.close();
  if (this->out.is_open())
    this->out.close();
}

const std::string	&Named_pipe::Get_pathin() const
{
  return (this->path_in);
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
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::runtime_error("Impossible to open " + this->path_in);
    }
}

void	Named_pipe::open_out(void)
{
  this->out.open(this->path_out, std::ofstream::out);
  if (!this->out.is_open())
    {
      std::remove(this->path_in.c_str());
      std::remove(this->path_out.c_str());
      throw std::runtime_error("Impossible to open " + this->path_out);
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
  std::cout << "Sending : file = " << command.file << ", threads = " << command.threads << ", data = ";
  for (unsigned int i = 0; i < command.data.size(); i++)
    std::cout << " " << command.data[i];
  std::cout << std::endl;
  this->out << command.file << " " << command.information << " " << command.threads;
  std::for_each(command.data.begin(), command.data.end(), [&](const std::string &str) { this->out << str << " "; });
  this->out << std::endl;
  return (*this);
}

Named_pipe		&Named_pipe::operator>>(t_command &command)
{
  int			info;
  std::stringstream	streamline;
  std::string		line;
  std::streambuf	*pbuf;
  std::streamsize	size;
  std::string		str;

  if (!this->checkFifo(this->path_in))
    return (*this);
  pbuf = this->in.rdbuf();
  size = pbuf->in_avail();
  if (size == 0)
    return (*this);
  getline(this->in, line);
  streamline << line;
  if (streamline.str()[0] == ' ')
    command.file = "";
  else
    streamline >> command.file;
  streamline >> info;
  command.information = static_cast<Information>(info);
  streamline >> command.threads;
  streamline >> str;
  while (str != "")
    {
      command.data.push_back(str);
      streamline >> str;
    }
  std::cout << "Receiving : file = " << command.file << ", threads = " << command.threads << ", data = ";
  for (unsigned int i = 0; i < command.data.size(); i++)
    std::cout << command.data[i] << "|";
  std::cout << std::endl;
  return (*this);
}
