//
// ui.cpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:28:02 2017 Nathan Scutari
// Last update Sun Apr 30 16:32:48 2017 Nathan Scutari
//

#include <iostream>
#include "ui.hpp"

Ui::Ui(int threads)
  : win(NULL), main(NULL), txt(NULL), input(""), last_event(0), font(), threads(threads), orders()
{
  char		center[] = "SDL_VIDEO_WINDOW_POS=center";

  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) == -1 ||
      TTF_Init() == -1 || (font = TTF_OpenFont("./font.ttf", 18)) == NULL)
    throw std::exception();
  SDL_EnableUNICODE(1);
  SDL_EnableKeyRepeat(0, 0);
  if ((win = SDL_SetVideoMode(1280, 900, 32,
			      SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::exception();
  init_main_surface();
}

void	Ui::init_main_surface()
{
  SDL_Rect	pos;
  SDL_Surface	*line;

  main = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 900, 32, 0, 0, 0, 0);
  line = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 1, 32, 0, 0, 0, 0);
  pos.x = 0;
  pos.y = 820;
  SDL_FillRect(main, NULL, SDL_MapRGB(win->format, 255, 255, 255));
  SDL_FillRect(line, NULL, SDL_MapRGB(win->format, 0, 0, 0));
  SDL_BlitSurface(line, NULL, main, &pos);
  SDL_FreeSurface(line);
  line = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 820, 32, 0, 0, 0, 0);
  pos.x = 980;
  pos.y = 0;
  SDL_FillRect(line, NULL, SDL_MapRGB(win->format, 0, 0, 0));
  SDL_BlitSurface(line, NULL, main, &pos);
  SDL_FreeSurface(line);
}

Ui::~Ui()
{}

void	Ui::update_text_surface(bool diff)
{
  SDL_Color	color = {0, 0, 0};
  SDL_Color	bg = {255, 255, 255};

  if (diff)
    {
      if (txt)
	SDL_FreeSurface(txt);
      txt = TTF_RenderText_Shaded(font, input.c_str(), color, bg);
    }
}

int	Ui::get_user_input(void)
{
  bool		end = false;
  bool		diff = false;
  SDL_Event	event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
	input = "exit";
      else if (event.key.keysym.unicode >= 32 && event.key.keysym.unicode <= 255 &&
	       last_event != event.key.keysym.unicode)
	input += event.key.keysym.unicode;
      else if (event.key.keysym.unicode == '\b' && input.size() > 0 &&
	       last_event != event.key.keysym.unicode)
	input.pop_back();
      if (event.key.keysym.sym == SDLK_RETURN && event.type == SDL_KEYDOWN)
	{
	  diff = true;
	  end = true;
	}
      if (last_event != event.key.keysym.unicode)
	{
	  last_event = event.key.keysym.unicode;
	  diff = true;
	}
    }
  update_text_surface(diff);
  return ((end == true) ? 1 : 0);
}

void	Ui::print_txt()
{
  SDL_Rect	pos;

  pos.x = 50;
  pos.y = 840;
  SDL_BlitSurface(txt, NULL, win, &pos);
}

std::vector<std::string>	Ui::get_order_lines(std::vector<std::string> &data)
{
  bool				empty = false;
  std::vector<std::string>	txt;
  std::string			line;
  int				pos = 0;

  while (!empty)
    {
      line.clear();
      while (line.size() <= 50)
	{
	  ++pos;
	  if (pos > data.size())
	    {
	      empty = true;
	      break;
	    }
	  if (line.size() + data[pos - 1].size() + 3 <= 50)
	    line += data[pos - 1] + " | ";
	  else
	    break;
	}
      txt.push_back(line);
    }
  return (txt);
}

void	Ui::addOrder(t_command &order)
{
  std::vector<std::string>	info = {"PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS"};
  std::string	tmp;
  SDL_Color	txt = {0, 0, 0};
  SDL_Color	bg = {255, 255, 255};
  t_order	new_order;

  tmp = "File: " + order.file;
  new_order.file = TTF_RenderText_Shaded(font, tmp.c_str(), txt, bg);
  tmp = "Information: " + info[static_cast<int>(order.information)];
  new_order.information = TTF_RenderText_Shaded(font, tmp.c_str(), txt, bg);
  info = get_order_lines(order.data);
  info[0] = "Result: " + info[0];
  for (int i = 0 ;  i < info.size() ; ++i)
    {
      new_order.txt.push_back(TTF_RenderText_Shaded(font, info[i].c_str(), txt, bg));
    }
  orders.push_back(new_order);
}

void	Ui::print_orders(void)
{
  SDL_Rect	pos;

  pos.x = 0;
  pos.y = 0;
  SDL_BlitSurface(orders[0].file, NULL, win, &pos);
  pos.x = orders[0].file->w + 20;
  SDL_BlitSurface(orders[0].information, NULL, win, &pos);
  pos.y = orders[0].file->h + 5;
  pos.x = 0;
  for (int i = 0 ; i < orders[0].txt.size() ; ++i)
    {
      SDL_BlitSurface(orders[0].txt[i], NULL, win, &pos);
      pos.y += orders[0].file->h + 5;
    }
}

std::string	Ui::refresh(void)
{
  std::string	ret("");

  SDL_BlitSurface(main, NULL, win, NULL);
  if (get_user_input())
    {
      ret = input;
      input = "";
    }
  print_txt();
  print_orders();
  SDL_Flip(win);
  return (ret);
}
