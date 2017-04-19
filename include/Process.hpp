//
// Process.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza/include
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Wed Apr 19 11:11:25 2017 Nathan Scutari
// Last update Wed Apr 19 11:54:11 2017 Nathan Scutari
//

#ifndef __PROCESS_HPP__
# define __PROCESS_HPP__

class Process
{
private:
  int	t_nbr;
  int	id;

private:
  Process(Process &);
  Process	&operator=(Process &);
  Process();

public:
  Process(int, int);
  ~Process();

  int	is_full();
};

#endif // !__PROCESS_HPP__
