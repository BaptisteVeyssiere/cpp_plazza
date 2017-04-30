//
// Created by ilyas on 27/04/17.
//

#ifndef PLAZZA_FINDER_HPP
#define PLAZZA_FINDER_HPP

#include <vector>
#include <string>

class Finder {

private:
  Finder();
  ~Finder();

  static long matchCount(std::vector<char> const &mem);
  static long findXor(std::vector<char> const& mem, std::vector<std::pair<std::vector<unsigned char>, long>> analyse);
  static long findCaesar(std::vector<char> const& mem, std::vector<std::pair<unsigned char, long>> analyse);
  static void findCaesarValues(std::vector<std::string> &data, std::vector<char> const& mem, unsigned char key, std::function<void(std::vector<std::string> &, std::string const &)> finding);
  static void findXorValues(std::vector<std::string> &data, std::vector<char> const& mem, std::vector<unsigned char> key, std::function<void(std::vector<std::string> &, std::string const &)> finding);

public:
  static void findMail(std::vector<std::string> &data, std::string const& mem);
  static void findIP(std::vector<std::string> &data, std::string const& mem);
  static void findPhone(std::vector<std::string> &data, std::string const& mem);

  static void findMailCiphered(std::vector<std::string> &data, std::vector<char> const& mem);
  static void findIPCiphered(std::vector<std::string> &data, std::vector<char> const& mem);
  static void findPhoneCiphered(std::vector<std::string> &data, std::vector<char> const& mem);

};


#endif //PLAZZA_FINDER_HPP
