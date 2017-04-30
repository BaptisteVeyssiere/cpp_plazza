//
// ui.hpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:25:31 2017 Nathan Scutari
// Last update Sun Apr 30 15:14:02 2017 Nathan Scutari
//

#ifndef __UI_HPP__
# define __UI_HPP__

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

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

  void	init_main_surface(void);
  int	get_user_input(void);
  void	update_text_surface(bool);
  void	print_txt(void);

public:
  Ui();
  ~Ui();

  std::string	refresh(void);
};

#endif // !__UI_HPP__
