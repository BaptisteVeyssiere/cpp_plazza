//
// Parser.cpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/src
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:42:14 2017 Baptiste Veyssiere
// Last update Sat Apr 29 14:27:54 2017 Baptiste Veyssiere
//

#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

void	Parser::epur_string(std::string &command) const
{
  for (std::string::iterator it = command.begin(); it != command.end(); it++)
    {
      if ((it == command.begin() && std::isspace(*it)) ||
	  (std::isspace(*it) && (std::isspace(*std::next(it)) || std::next(it) == command.end())))
	{
	  command.erase(it);
	  --it;
	}
      else if (std::isspace(*it))
	*it = ' ';
    }
}

bool	Parser::is_empty(const std::string &str) const
{
  for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
    if (std::isspace(*it) == false)
      return (false);
  return (true);
}

void	Parser::fileExists(const std::string &name) const
{
  struct stat	buf;

  if (stat(name.c_str(), &buf) == -1)
    throw parser_exception("The file named " + name + " doesn't exist");
}

void	Parser::create_command(const std::string &file, const std::string &information, std::vector<t_command> &command_list) const
{
  t_command	command = { file, Information::PHONE_NUMBER, 0, {} };
  std::vector<std::string>	information_list =
    {
      "PHONE_NUMBER",
      "EMAIL_ADDRESS",
      "IP_ADDRESS"
    };
  std::size_t			i;

  for (i = 0; i < information_list.size(); i++)
    if (information_list[i] == information)
      {
	command.information = static_cast<Information>(i);
	break;
      }
  this->fileExists(file);
  if (i > 2)
    throw parser_exception("Information type " + information + " was not recognized");
  command_list.push_back(command);
}

void	Parser::create_order(const std::string &command, std::vector<t_command> &command_list) const
{
  std::stringstream			stream(command);
  std::istream_iterator<std::string>	begin(stream);
  std::istream_iterator<std::string>	end;
  std::vector<std::string>		word_vector(begin, end);

  if (word_vector.size() < 2)
    throw parser_exception("Incomplete command");
  for (std::vector<std::string>::iterator it = word_vector.begin(); it != std::prev(word_vector.end()); it++)
    this->create_command(*it, *std::prev(word_vector.end()), command_list);
}

void	Parser::parse(std::string &command, std::vector<t_command> &command_list) const
{
  std::vector<std::string>	list;
  std::size_t			prev;
  std::size_t			pos;
  std::vector<std::string>	command_vector;

  this->epur_string(command);
  prev = 0;
  while ((pos = command.find_first_of(";", prev)) != std::string::npos)
    {
      if (pos > prev)
	command_vector.push_back(command.substr(prev, pos - prev));
      prev = pos + 1;
    }
  if (prev < command.length())
    command_vector.push_back(command.substr(prev, std::string::npos));
  for (unsigned int i = 0; i < command_vector.size(); i++)
    {
      if (this->is_empty(command_vector[i]) == false)
	{
	  this->epur_string(command_vector[i]);
	  this->create_order(command_vector[i], command_list);
	}
    }
}
