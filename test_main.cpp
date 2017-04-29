//
// test_main.cpp for test in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:36:47 2017 Nathan Scutari
// Last update Sat Apr 29 15:29:46 2017 Nathan Scutari
//

#include <iostream>
#include "ui.hpp"

int	main(void)
{
  std::string	ret;
  Ui	interface;

  for (int i = 0 ; i < 3000 ; ++i)
    {
      ret = interface.refresh();
      if (ret != "")
	std::cout << ret << std::endl;
    }
  return (0);
}
