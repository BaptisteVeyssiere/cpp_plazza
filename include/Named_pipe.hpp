//
// Created by veyssi_b on 20/04/17.
//

#ifndef __NAMED_PIPE_HPP__
# define __NAMED_PIPE_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include "sys/stat.h"
#include "sys/types.h"
#include "command.hpp"

class   Named_pipe
{
private:
  std::ifstream   in;
  std::ofstream   out;
  std::string     path_in;
  std::string     path_out;

public:
  Named_pipe(const std::string &, const std::string &, bool);
  Named_pipe(const Named_pipe &);
  Named_pipe  &operator=(const Named_pipe &);
  virtual ~Named_pipe();
  Named_pipe	&operator<<(const t_command &);
  Named_pipe	&operator>>(t_command &);
  bool	checkFifo(const std::string &) const;
  void	open_in(void);
  void	open_out(void);
  void	close_in(void);
  void	close_out(void);
  const std::string	&Get_pathin() const;
  void	release();
};

#endif // __NAMED_PIPE_HPP__
