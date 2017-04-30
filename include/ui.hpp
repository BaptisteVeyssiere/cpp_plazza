//
// ui.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:25:31 2017 Nathan Scutari
// Last update Sun Apr 30 16:22:44 2017 Nathan Scutari
//

#ifndef __UI_HPP__
# define __UI_HPP__

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "command.hpp"

class Ui
{
private:
  typedef struct	s_order
  {
    SDL_Surface			*file;
    SDL_Surface			*information;
    std::vector<SDL_Surface *>	txt;
  }			t_order;

private:
  SDL_Surface	*win;
  SDL_Surface	*main;
  SDL_Surface	*txt;
  int		last_event;
  std::string	input;
  TTF_Font	*font;
  int		threads;
  std::vector<t_order>	orders;

private:
  Ui(Ui &);
  Ui	&operator=(Ui &);

  void				init_main_surface(void);
  int				get_user_input(void);
  void				update_text_surface(bool);
  void				print_txt(void);
  std::vector<std::string>	get_order_lines(std::vector<std::string> &);
  void				print_orders(void);

public:
  Ui(int);
  ~Ui();

  std::string	refresh(void);
  void		addOrder(t_command &);
};

#endif // !__UI_HPP__
