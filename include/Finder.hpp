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
  static void findXor(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem, std::function<void(std::vector<std::string> &data, std::string const& mem)> finding);
  static void findCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem, std::function<void(std::vector<std::string> &data, std::string const& mem)> finding);

public:
  static void findMail(std::vector<std::string> &data, std::string const& mem);
  static void findIP(std::vector<std::string> &data, std::string const& mem);
  static void findPhone(std::vector<std::string> &data, std::string const& mem);

  static void findMailXor(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);
  static void findIPXor(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);
  static void findPhoneXor(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);

  static void findMailCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);
  static void findIPCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);
  static void findPhoneCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);

  static void findMailCiphered(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);
  static void findIPCiphered(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);
  static void findPhoneCiphered(std::vector<std::vector<std::string>> &data, std::vector<char> const& mem);

};


#endif //PLAZZA_FINDER_HPP
