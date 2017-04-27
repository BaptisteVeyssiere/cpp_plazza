//
// parser_exception.hpp for Project-Master in /home/veyssi_b/rendu/tek2/CPP/cpp_plazza/include
//
// Made by Baptiste Veyssiere
// Login   <veyssi_b@epitech.net>
//
// Started on  Mon Apr 17 21:49:36 2017 Baptiste Veyssiere
// Last update Mon Apr 17 21:55:42 2017 Baptiste Veyssiere
//

#ifndef __PARSER_EXCEPTION_HPP__
# define __PARSER_EXCEPTION_HPP__

#include <string>
#include <stdexcept>

class	parser_exception : public std::exception
{
public:
  ~parser_exception() noexcept {}
  parser_exception(std::string const &msg):
    _msg(msg) {}
  const char* what() const throw()
  { return _msg.c_str(); }
private:
  std::string	_msg;
};

#endif // !__PARSER_EXCEPTION_HPP__
