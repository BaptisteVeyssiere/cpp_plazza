//
// ui.cpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:28:02 2017 Nathan Scutari
// Last update Sun Apr 30 17:45:49 2017 Nathan Scutari
//

#include <iostream>
#include "ui.hpp"

Ui::Ui(int threads)
  : win(NULL), main(NULL), txt(NULL), separator(NULL), input(""), last_event(0), font(), threads(threads), orders()
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

  separator = SDL_CreateRGBSurface(SDL_HWSURFACE, 980, 1, 32, 0, 0, 0, 0);
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
	{
	  end = true;
	  input = "exit";
	}
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
      while (line.size() <= 90)
	{
	  if (pos >= data.size())
	    {
	      empty = true;
	      break;
	    }
	  if (line.size() + data[pos].size() + 3 <= 90)
	    {
	      line += data[pos] + " | ";
	      ++pos;
	    }
	  else
	    break;
	}
      txt.push_back(line);
    }
  return (txt);
}

void	Ui::updateOrderSize(t_order &order)
{
  int	data;
  int	size;

  size = order.file->h + 5;
  data = order.txt.size() - 1;
  if (data < 0)
    data = 0;
  size += data * 5 + (data + 1) * order.file->h;
  order.h = size;
}

void	Ui::addOrder(t_command &order)
{
  std::vector<std::string>	info = {"PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS"};
  std::string	tmp;
  SDL_Color	head = {0, 0, 170};
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
  updateOrderSize(new_order);
  orders.push_back(new_order);
}

void	Ui::print_order_nbr(int i, int y)
{
  SDL_Rect	pos;

  y -= (orders[i].h + 10);
  pos.x = 0;
  pos.y = y;
  SDL_BlitSurface(separator, NULL, win, &pos);
  pos.y += 10;
  SDL_BlitSurface(orders[i].file, NULL, win, &pos);
  pos.x = orders[i].file->w + 20;
  SDL_BlitSurface(orders[i].information, NULL, win, &pos);
  pos.x = 0;
  pos.y += orders[i].file->h + 5;
  for (int x = 0 ; x < orders[i].txt.size() ; ++x)
    {
      SDL_BlitSurface(orders[i].txt[x], NULL, win, &pos);
      pos.y += orders[0].file->h + 5;
    }
}

void	Ui::print_orders(void)
{
  int		y;
  SDL_Rect	pos;

  pos.x = 0;
  y = 820;
  for (int i = orders.size() - 1 ; i >= 0 ; --i)
    {
      print_order_nbr(i, y);
      y -= (orders[i].h + 20);
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
