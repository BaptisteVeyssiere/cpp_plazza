//
// test_main.cpp for test in /home/scutar_n/rendu/CPP/cpp_plazza
//
// Made by Nathan Scutari
// Login   <scutar_n@epitech.net>
//
// Started on  Sat Apr 29 10:36:47 2017 Nathan Scutari
// Last update Sun Apr 30 17:39:46 2017 Nathan Scutari
//

#include <iostream>
#include "ui.hpp"

int	main(void)
{
  std::string	ret;
  Ui	interface(3);
  t_command	order{"Makefile", Information::PHONE_NUMBER, 0, {"12345678", "1 25 52626 277", "mzaeazeiazjek", "iazejzeirkjezikeriotkernk", "azeoazieak", "oakzeioazkeja", "aziejaziejazie", "azeoazkeiojazkel", "poiuyiuhnjuyhhjuh", "ohbvfyjhgfvhygvb", "khgbnjhgftyuhgfgytfv", "kjbgvugfvbjuygvbjuyg", "nbhjkgvbnjuygbhy", "bhjiuyghjuyghuh", "bgyuiuyghjyg", "nbhjkiuyhjuyghgfv", "bvgytdfghgdfgtrdcfrd", "nbvfrtyuioouytrdcv", "bvfyutdcvhgfvb", "wwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwwwwwww", "wwwwwwwwwwwwww"}};
  t_command	order2{"Plazza", Information::IP_ADDRESS, 0, {"alzeazlekz", "azieiaze,", "azekazeaze", "98:2983:283:2873"}};
  t_command	order3{"jpp", Information::EMAIL_ADDRESS, 0, {"azekaz,ea", "iazejiazej", "iazejaizejaize", "aziejaziejaziejazie", "aziejaziejaziejazie", "aziejaziejaize"}};

  interface.addOrder(order);
  interface.addOrder(order2);
  interface.addOrder(order3);
  for (int i = 0 ; i < 3000 ; ++i)
    {
      ret = interface.refresh();
      if (ret != "")
	std::cout << ret << std::endl;
    }
  return (0);
}
