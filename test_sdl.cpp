//
// test_sdl.cpp for test in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Fri Apr 28 21:40:55 2017 Nathan Scutari
// Last update Sat Apr 29 15:44:00 2017 Nathan Scutari
//

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


int	main(void)
{
  SDL_Event	event;
  SDL_Surface	*win;
  SDL_Surface	*main;
  SDL_Surface	*txt;
  char		center[] = "SDL_VIDEO_WINDOW_POS=center";
  std::string	input;
  bool		refresh = true;
  TTF_Font	*font;
  SDL_Color	color = {0, 0, 0};
  SDL_Color	bg = {255, 255, 255};
  int		last_event;

  if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) == -1)
    throw std::exception();
  TTF_Init();
  txt = NULL;
  font = TTF_OpenFont("./font.ttf", 30);
  SDL_putenv(center);
  SDL_EnableUNICODE(1);
  SDL_EnableKeyRepeat(0, 0);
  if ((win = SDL_SetVideoMode(1280, 720, 32,
			      SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    throw std::exception();
  main = SDL_CreateRGBSurface(0, 1280, 900, 32, 0, 0, 0, 0);
  SDL_FillRect(main, NULL, SDL_MapRGB(win->format, 255, 255, 255));
  while (refresh)
    {
      while (SDL_PollEvent(&event))
	{
	  if (event.type == SDL_QUIT)
	    refresh = false;
	  if (event.key.keysym.unicode >= 32 && event.key.keysym.unicode <= 255 &&
	      last_event != event.key.keysym.unicode)
	    {
	      input += event.key.keysym.unicode;
	      if (txt)
		SDL_FreeSurface(txt);
	      txt = TTF_RenderText_Shaded(font, input.c_str(), color, bg);
	    }
	  else if (event.key.keysym.unicode == '\b' && last_event != event.key.keysym.unicode &&
		   input.size() > 0)
	    {
	      input.pop_back();
	      if (txt)
		SDL_FreeSurface(txt);
	      txt = TTF_RenderText_Shaded(font, input.c_str(), color, bg);
	    }
	  last_event = event.key.keysym.unicode;
	}
      SDL_BlitSurface(main, NULL, win, NULL);
      SDL_BlitSurface(txt, NULL, win, NULL);
      SDL_Flip(win);
    }
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
  return (0);
}
