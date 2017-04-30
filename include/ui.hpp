//
// ui.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:25:31 2017 Nathan Scutari
// Last update Sun Apr 30 18:32:33 2017 Baptiste Veyssiere
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
    SDL_Surface			*file = NULL;
    SDL_Surface			*information = NULL;
    std::vector<SDL_Surface *>	txt = {};
    int				h = 0;
  }			t_order;

private:
  SDL_Surface	*win;
  SDL_Surface	*main;
  SDL_Surface	*txt;
  SDL_Surface	*separator;
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
  std::vector<std::string>	get_order_lines(const std::vector<std::string> &);
  void				print_orders(void);
  void				updateOrderSize(t_order &);
  void				print_order_nbr(int, int);

public:
  Ui(int);
  ~Ui();

  std::string	refresh(void);
  void		addOrder(const t_command &);
};

#endif // !__UI_HPP__
