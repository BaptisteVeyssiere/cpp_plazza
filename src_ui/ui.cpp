//
// ui.cpp for plazza in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:28:02 2017 Nathan Scutari
// Last update Sun Apr 30 23:24:49 2017 Baptiste Veyssiere
//

#include <iostream>
#include "ui.hpp"

Ui::Ui(int _threads)
  : win(NULL), main(NULL), txt(NULL), separator(NULL), last_event(0), input(""), font(), threads(_threads), orders(), status()
{
  char		center[] = "SDL_VIDEO_WINDOW_POS=center";

  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) == -1 ||
      TTF_Init() == -1 || (font = TTF_OpenFont("./font.ttf", 18)) == NULL)
    throw std::runtime_error("SDL / TTF Init failed");
  SDL_EnableUNICODE(1);
  SDL_EnableKeyRepeat(0, 0);
  SDL_putenv(center);
  if ((win = SDL_SetVideoMode(1280, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::runtime_error("SDL failed to open window");
  init_main_surface();
}

Ui::~Ui()
{
  SDL_FreeSurface(main);
  if (txt)
    SDL_FreeSurface(txt);
  SDL_FreeSurface(separator);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void	Ui::init_main_surface()
{
  SDL_Rect	pos;
  SDL_Surface	*line;

  if ((separator = SDL_CreateRGBSurface(SDL_HWSURFACE, 980, 1, 32, 0, 0, 0, 0)) == NULL ||
      (main = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 900, 32, 0, 0, 0, 0)) == NULL ||
      (line = SDL_CreateRGBSurface(SDL_HWSURFACE, 1280, 1, 32, 0, 0, 0, 0)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  pos.x = 0;
  pos.y = 820;
  SDL_FillRect(main, NULL, SDL_MapRGB(win->format, 255, 255, 255));
  SDL_FillRect(line, NULL, SDL_MapRGB(win->format, 0, 0, 0));
  SDL_BlitSurface(line, NULL, main, &pos);
  SDL_FreeSurface(line);
  if ((line = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 820, 32, 0, 0, 0, 0)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  pos.x = 980;
  pos.y = 0;
  SDL_FillRect(line, NULL, SDL_MapRGB(win->format, 0, 0, 0));
  SDL_BlitSurface(line, NULL, main, &pos);
  SDL_FreeSurface(line);
}

void	Ui::update_text_surface(bool diff)
{
  SDL_Color	color = {0, 0, 0, 255};
  SDL_Color	bg = {255, 255, 255, 255};

  if (diff)
    {
      if (input.size() > 0)
	{
	  if (txt)
	    SDL_FreeSurface(txt);
	  if ((txt = TTF_RenderText_Shaded(font, input.c_str(), color, bg)) == NULL)
	    throw std::runtime_error("SDL surface allocation failed");
	}
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
	  event.key.keysym.unicode = 0;
	}
      else if (event.key.keysym.unicode >= 32 && event.key.keysym.unicode <= 255 &&
	       last_event != event.key.keysym.unicode)
	input += static_cast<char>(event.key.keysym.unicode);
      else if (event.key.keysym.unicode == '\b' && input.size() > 0 &&
	       last_event != event.key.keysym.unicode)
	input.pop_back();
      else if (event.key.keysym.sym == SDLK_RETURN && event.type == SDL_KEYDOWN)
	{
	  diff = true;
	  end = true;
	  event.key.keysym.unicode = 0;
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
  if (input.size() > 0)
    SDL_BlitSurface(txt, NULL, win, &pos);
}

std::vector<std::string>	Ui::get_order_lines(const std::vector<std::string> &data)
{
  bool				empty = false;
  std::vector<std::string>	txte;
  std::string			line;
  int				pos = 0;

  while (!empty)
    {
      line.clear();
      while (line.size() <= 90)
	{
	  if (pos >= static_cast<int>(data.size()))
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
      txte.push_back(line);
    }
  return (txte);
}

void	Ui::updateOrderSize(t_order &order)
{
  int	data;
  int	size;

  size = order.file->h + 5;
  data = static_cast<int>(order.txt.size()) - 1;
  if (data < 0)
    data = 0;
  size += data * 5 + (data + 1) * order.file->h;
  order.h = size;
}

void	Ui::freeFrontOrder()
{
  if (orders[0].file)
    SDL_FreeSurface(orders[0].file);
  if (orders[0].information)
    SDL_FreeSurface(orders[0].information);
  for (int i = 0 ; i < static_cast<int>(orders[0].txt.size()) ; ++i)
    {
      if (orders[0].txt[i])
	SDL_FreeSurface(orders[0].txt[i]);
    }
  orders.erase(orders.begin());
}

void	Ui::releaseOutOfRange()
{
  int	x;
  int	y;

  y = 820;
  if (orders.size() == 0)
    return ;
  x = static_cast<int>(orders.size()) - 1;
  for (int i = static_cast<int>(orders.size() - 1) ; i >= 0 ; --i)
    {
      y -= (orders[i].h + 20);
      if (y <= 0)
	break;
      --x;
    }
  for (int i = 0 ; i <= x  ; ++i)
    freeFrontOrder();
}

void	Ui::addOrder(const t_command &order)
{
  std::vector<std::string>	info = {"PHONE_NUMBER", "EMAIL_ADDRESS", "IP_ADDRESS"};
  std::string	tmp;
  SDL_Color	head = {0, 0, 170, 255};
  SDL_Color	txte = {0, 0, 0, 255};
  SDL_Color	bg = {255, 255, 255, 255};
  SDL_Surface	*tmps;
  t_order	new_order;

  if (order.data.size() == 0)
    return ;
  tmp = "File: " + order.file;
  if ((new_order.file = TTF_RenderText_Shaded(font, tmp.c_str(), head, bg)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  tmp = "Information: " + info[static_cast<int>(order.information)];
  if ((new_order.information = TTF_RenderText_Shaded(font, tmp.c_str(), head, bg)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  info = get_order_lines(order.data);
  info[0] = "Result: " + info[0];
  for (int i = 0 ;  i < static_cast<int>(info.size()) ; ++i)
    {
      if ((tmps = TTF_RenderText_Shaded(font, info[i].c_str(), txte, bg)) == NULL)
	throw std::runtime_error("SDL surface allocation failed");
      new_order.txt.push_back(tmps);
    }
  updateOrderSize(new_order);
  orders.push_back(new_order);
  releaseOutOfRange();
}

void	Ui::print_order_nbr(int i, int y)
{
  SDL_Rect	pos;
  short		tmp;

  y -= (orders[i].h + 10);
  pos.x = 0;
  pos.y = static_cast<short>(y);
  tmp = pos.y;
  SDL_BlitSurface(separator, NULL, win, &pos);
  tmp = static_cast<short>(tmp + 10);
  pos.y = tmp;
  SDL_BlitSurface(orders[i].file, NULL, win, &pos);
  pos.x = static_cast<short>(orders[i].file->w + 20);
  SDL_BlitSurface(orders[i].information, NULL, win, &pos);
  pos.x = 0;
  tmp = static_cast<short>(tmp + orders[i].file->h + 5);
  pos.y = tmp;
  for (int x = 0 ; x < static_cast<int>(orders[i].txt.size()); ++x)
    {
      SDL_BlitSurface(orders[i].txt[x], NULL, win, &pos);
      tmp = static_cast<short>(tmp + orders[0].file->h + 5);
      pos.y = tmp;
    }
}

void	Ui::updateProcessStatus(int i, std::vector<int> &p_thread, std::vector<int> &p_id)
{
  SDL_Color	bg = {255, 255, 255, 255};
  SDL_Color	head = {180, 0, 0, 255};
  SDL_Color	black = {0, 0, 0, 255};
  std::string	tmp;
  SDL_Surface	*temp;
  int		queue;

  tmp = "Process " + std::to_string(p_id[i]) + ":";
  if ((temp = TTF_RenderText_Shaded(font, tmp.c_str(), head, bg)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  status.push_back(temp);
  queue = (p_thread[i] >= threads) ? p_thread[i] - threads : 0;
  tmp = "Orders in queue: " + std::to_string(queue);
  if ((temp = TTF_RenderText_Shaded(font, tmp.c_str(), black, bg)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  status.push_back(temp);
  tmp = "Threads running: " + std::to_string(p_thread[i] - queue);
  if ((temp = TTF_RenderText_Shaded(font, tmp.c_str(), black, bg)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  status.push_back(temp);
}

void	Ui::clearStatus()
{
  for (int i = 0 ; i < static_cast<int>(status.size()) ; ++i)
    {
      if (status[i])
	SDL_FreeSurface(status[i]);
    }
  status.clear();
}

void	Ui::updateStatus(std::vector<int> p_thread, std::vector<int> p_id)
{
  SDL_Color	bg = {255, 255, 255, 255};
  SDL_Color	head = {0, 0, 180, 255};
  std::string	tmp;
  SDL_Surface	*temp;

  clearStatus();
  tmp = "Processes alive: " + std::to_string(p_thread.size());
  if ((temp = TTF_RenderText_Shaded(font, tmp.c_str(), head, bg)) == NULL)
    throw std::runtime_error("SDL surface allocation failed");
  status.push_back(temp);
  for (int i = 0 ; i < static_cast<int>(p_thread.size()) ; ++i)
    updateProcessStatus(i, p_thread, p_id);
}

void	Ui::print_orders(void)
{
  int		y;

  y = 820;
  for (int i = static_cast<int>(orders.size() - 1); i >= 0 ; --i)
    {
      print_order_nbr(i, y);
      y -= (orders[i].h + 20);
    }
}

void	Ui::print_status(void)
{
  SDL_Rect	pos;

  if (status.size() == 0)
    return;
  pos.x = 990;
  pos.y = 10;
  SDL_BlitSurface(status[0], NULL, win, &pos);
  pos.y = static_cast<short>(pos.y + 20 + status[0]->h);
  for (int i = 1 ; i < static_cast<int>(status.size()) ; ++i)
    {
      SDL_BlitSurface(status[i], NULL, win, &pos);
      pos.y = static_cast<short>(pos.y + 5 + status[0]->h);
      if (i % 3 == 0)
	pos.y = static_cast<short>(pos.y + 20 + status[0]->h);
      if (pos.y >= 790)
	break;
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
  print_status();
  SDL_Flip(win);
  return (ret);
}
