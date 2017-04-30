//
// Created by ilyas on 27/04/17.
//

#include <regex>
#include <iostream>
#include "Finder.hpp"
#include "Decrypt.hpp"

Finder::Finder() {

}

Finder::~Finder() {

}

void Finder::findMail(std::vector<std::string> &data, std::string const &mem) {
  std::regex  reg("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
  std::smatch mail;
  std::string content = mem;

  while (std::regex_search(content, mail, reg)) {
    data.push_back(mail.str());
    content = mail.suffix().str();
  }
}

void Finder::findIP(std::vector<std::string> &data, std::string const &mem) {
  std::regex  reg("([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])");
  std::smatch ip;
  std::string content = mem;

  while (std::regex_search(content, ip, reg)) {
    data.push_back(ip.str());
    content = ip.suffix().str();
  }
}

void Finder::findPhone(std::vector<std::string> &data, std::string const &mem) {
  std::regex  reg("([0-9]|[0-9] ){10}");
  std::smatch phone;
  std::string content = mem;

  while (std::regex_search(content, phone, reg)) {
    data.push_back(phone.str());
    content = phone.suffix().str();
  }
}

long    Finder::matchCount(std::vector<char> const &mem)
{
  long  count = 0;
  for (long i = 0; i < mem.size(); i++)
  {
    if ((mem[i] > 0 && mem[i] < 9) || (mem[i] > 13 && mem[i] < 32)) {
      count -= 4;
    } else if (i + 2 < mem.size() && mem[i] == mem[i + 1] && mem[i + 1] == mem[i + 2]) {
      count -= 5;
    } else if (i + 1 < mem.size() && mem[i] == mem[i + 1]) {
      count -= 2;
    } else if ((mem[i] > 47 && mem[i] < 58) || (mem[i] > 64 && mem[i] < 91)
               || (mem[i] > 96 && mem[i] < 123)) {
      if (i + 1 < mem.size() && i > 0 && (mem[i] > 47 && mem[i] < 58) &&
          ((mem[i + 1] > 64 && mem[i + 1] < 91) || (mem[i + 1] > 96 && mem[i + 1] < 123)))
        count -= 10;
      else if (i - 1 > 0 &&
               (mem[i - 1] == '>' || mem[i - 1] == '#' || mem[i - 1] == '%' ||
                mem[i - 1] == '$' || mem[i - 1] == '^' || mem[i - 1] == '~' ||
                mem[i - 1] == ')' || mem[i - 1] == ']' || mem[i - 1] == '}' ||
                mem[i - 1] == '|'))
        count -= 10;
      else if (i + 1 < mem.size() &&
               (mem[i + 1] == '<' || mem[i + 1] == '#' || mem[i + 1] == '%' ||
                mem[i + 1] == '$' || mem[i + 1] == '^' || mem[i + 1] == '~' ||
                mem[i + 1] == '(' || mem[i + 1] == '[' || mem[i + 1] == '{' ||
                mem[i + 1] == '|'))
        count -= 10;
      else {
        count += 10;
      }
    } else if ((i + 1 < mem.size() &&
                (mem[i] == '.' || mem[i] == ';' || mem[i] == '!' || mem[i] == '?')
                && mem[i + 1] != ' ' && mem[i + 1] != '\t' && mem[i + 1] != '\n')) {
      count -= 2;
    }
  }
  return (count);
}

void Finder::findCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem,
                        std::function<void(std::vector<std::string> &data, std::string const &mem)> finding) {
  std::vector<std::pair<unsigned char, long>>      analyse;
  unsigned char key;
  long  max = -9223372036854775807;
  key = 0;
  while (key <= 255) {
    std::vector<char> decryptMem = mem;
    Decrypt::caesarDecrypt(decryptMem, key);
    std::string memory(decryptMem.data());
    if (decryptMem[0] != '\0' && memory.size() == mem.size()) {
      long tmp = Finder::matchCount(decryptMem);
      if (tmp > max)
        max = tmp;
      analyse.push_back(std::make_pair(key, tmp));
    }
    if (key == 255)
      break;
    ++key;
  }
  for (int i = 0; i < analyse.size(); i++) {
    if (analyse[i].second == max) {
      std::vector<char> decryptMem = mem;
      Decrypt::caesarDecrypt(decryptMem, analyse[i].first);
      std::string memory(decryptMem.data());
      std::vector<std::string> list;
      finding(list, memory);
      if (list.size() > 0) {
        data.push_back(list);
      }
    }
  }
  std::cout << "result=" << analyse.size() << std::endl;
}

void Finder::findXor(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem,
                     std::function<void(std::vector<std::string> &data, std::string const& mem)> finding) {
    std::vector<std::pair<std::vector<unsigned char>, long>>      analyse;
    std::vector<unsigned char> key;
    long  max = -9223372036854775807;
    key.push_back(0);
    while (key[0] <= 255) {
      std::vector<char> decryptMem = mem;
      Decrypt::xorDecrypt(decryptMem, key);
      std::string memory(decryptMem.data());
      if (decryptMem[0] != '\0' && memory.size() == mem.size()) {
        long tmp = Finder::matchCount(decryptMem);
        if (tmp > max)
          max = tmp;
        analyse.push_back(std::make_pair(key, tmp));
      }
      if (key[0] == 255)
        break;
      ++key[0];
    }
    key[0] = 0;
    key.push_back(1);
    while (key[0] <= 255) {
      while (key[1] <= 255) {
        std::vector<char> decryptMem = mem;
        Decrypt::xorDecrypt(decryptMem, key);
        std::string       memory(decryptMem.data());
        if (decryptMem[0] != '\0' && memory.size() == mem.size()) {
          long tmp = Finder::matchCount(decryptMem);
          if (tmp > max)
            max = tmp;
          analyse.push_back(std::make_pair(key, tmp));
        }
        if (key[1] == 255)
          break;
        ++key[1];
      }
      if (key[0] == 255)
        break;
      ++key[0];
      key[1] = 0;
    }
    for (int i = 0; i < analyse.size(); i++) {
      if (analyse[i].second == max) {
        std::vector<char> decryptMem = mem;
        Decrypt::xorDecrypt(decryptMem, analyse[i].first);
        std::string memory(decryptMem.data());
        std::vector<std::string> list;
        finding(list, memory);
        if (list.size() > 0) {
          data.push_back(list);
        }
      }
    }
    std::cout << "result=" << analyse.size() << std::endl;
}

void Finder::findMailXor(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findXor(data, mem, Finder::findMail);
}

void Finder::findIPXor(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findXor(data, mem, Finder::findIP);
}

void Finder::findPhoneXor(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findXor(data, mem, Finder::findPhone);
}

void Finder::findMailCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findCaesar(data, mem, Finder::findMail);
}

void Finder::findIPCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findCaesar(data, mem, Finder::findIP);
}

void Finder::findPhoneCaesar(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findCaesar(data, mem, Finder::findPhone);
}

void Finder::findMailCiphered(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findMailCaesar(data, mem);
  Finder::findMailXor(data, mem);
}

void Finder::findIPCiphered(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findIPCaesar(data, mem);
  Finder::findIPXor(data, mem);
}

void Finder::findPhoneCiphered(std::vector<std::vector<std::string>> &data, std::vector<char> const &mem) {
  Finder::findPhoneCaesar(data, mem);
  Finder::findPhoneXor(data, mem);
}