//
// Process.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:11:25 2017 Nathan Scutari
// Last update Thu Apr 20 15:06:56 2017 Nathan Scutari
//

#ifndef __PROCESS_HPP__
# define __PROCESS_HPP__

class Process
{
private:
  int	t_nbr;

private:
  Process(Process &);
  Process	&operator=(Process &);
  Process();

public:
  Process(int);
  ~Process();

  int	clone(int);
};

#endif // !__PROCESS_HPP__
