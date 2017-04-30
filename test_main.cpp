//
// test_main.cpp for test in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:36:47 2017 Nathan Scutari
// Last update Sun Apr 30 16:33:48 2017 Nathan Scutari
//

#include <iostream>
#include "ui.hpp"

int	main(void)
{
  std::string	ret;
  Ui	interface(3);
  t_command	order{"Makefile", Information::PHONE_NUMBER, 0, {"12345678", "1 25 52626 277", "mzaeazeiazjek", "iazejzeirkjezikeriotkernk", "azeoazieak", "oakzeioazkeja", "aziejaziejazie", "azeoazkeiojazkel"}};

  interface.addOrder(order);
  for (int i = 0 ; i < 3000 ; ++i)
    {
      ret = interface.refresh();
      if (ret != "")
	std::cout << ret << std::endl;
    }
  return (0);
}
