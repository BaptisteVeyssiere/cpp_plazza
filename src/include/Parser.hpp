//
// Parser.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/include
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Thu Apr 13 18:34:56 2017 Baptiste Veyssiere
// Last update Mon Apr 17 21:51:44 2017 Baptiste Veyssiere
//

#ifndef __PARSER_HPP__
# define __PARSER_HPP__

# include <vector>
# include <string>
# include <sstream>
# include <iterator>
# include <sys/stat.h>
# include "command.hpp"
# include "parser_exception.hpp"

class	Parser
{
private:
  Parser(const Parser &);
  Parser &operator=(const Parser &);

public:
  Parser();
  virtual ~Parser();
  void	parse(std::string &, std::vector<t_command> &) const;

private:
  void	epur_string(std::string &) const;
  bool	is_empty(const std::string &) const;
  void	create_order(const std::string &, std::vector<t_command> &) const;
  void	create_command(const std::string &, const std::string &, std::vector<t_command> &) const;
  void	fileExists(const std::string &) const;
};

#endif // !__PARSER_HPP__
