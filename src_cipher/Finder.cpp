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

void Finder::mail(std::vector<std::string> &data, std::string const& mem)
{
  std::regex  reg("[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+");
  std::smatch mail;
  std::string content = mem;

  while (std::regex_search(content, mail, reg)) {
    data.push_back(mail.str());
    content = mail.suffix().str();
  }
}

void Finder::ip(std::vector<std::string> &data, std::string const& mem)
{
    std::regex  reg("([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])\\.([2][0-5][0-5]|[1][0-9][0-9]|[1-9][0-9]|[0-9])");
  std::smatch ip;
  std::string content = mem;

  while (std::regex_search(content, ip, reg)) {
    data.push_back(ip.str());
    content = ip.suffix().str();
  }
}

void Finder::phone(std::vector<std::string> &data, std::string const& mem)
{
  std::regex  reg("([0-9]|[0-9] ){10}");
  std::smatch phone;
  std::string content = mem;

  while (std::regex_search(content, phone, reg)) {
    data.push_back(phone.str());
    content = phone.suffix().str();
  }
}

void Finder::findMail(std::vector<std::string> &data, std::vector<char> const& mem) {
  std::string tmp(mem.data());
  mail(data, tmp);
}

void Finder::findIP(std::vector<std::string> &data, std::vector<char> const& mem) {
  std::string tmp(mem.data());
  ip(data, tmp);
}

void Finder::findPhone(std::vector<std::string> &data, std::vector<char> const& mem) {
  std::string tmp(mem.data());
  phone(data, tmp);
}

long    Finder::matchCount(std::vector<char> const &mem)
{
  long  count = 0;
  for (size_t i = 0; i < mem.size(); i++)
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

long Finder::findCaesar(std::vector<char> const &mem, std::vector<std::pair<unsigned char, long>> &analyse) {
  unsigned char key;
  long  max = -9223372036854775807;
  key = 0;
  while (1) {
    std::vector<char> decryptMem = mem;
    Decrypt::caesarDecrypt(decryptMem, key);
    std::string memory(decryptMem.data());
    if (decryptMem[0] != '\0' && memory.size() >= mem.size()) {
      long tmp = Finder::matchCount(decryptMem);
      if (tmp > max)
        max = tmp;
      analyse.push_back(std::make_pair(key, tmp));
    }
    if (key == 255)
      break;
    ++key;
  }
  return (max);
}

long Finder::findXor(std::vector<char> const &mem, std::vector<std::pair<std::vector<unsigned char>, long>> &analyse) {
    std::vector<unsigned char> key;
    long  max = -9223372036854775807;
    key.push_back(0);
    while (1) {
      std::vector<char> decryptMem = mem;
      Decrypt::xorDecrypt(decryptMem, key);
      std::string memory(decryptMem.data());
      if (decryptMem[0] != '\0' && memory.size() >= mem.size()) {
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
    while (1) {
      while (1) {
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
  return (max);
}

void Finder::findCaesarValues(std::vector<std::string> &data, std::vector<char> const &mem, unsigned char key,
                              std::function<void(std::vector<std::string> &, std::string const &)> finding){
  std::vector<char> decryptMem = mem;
  Decrypt::caesarDecrypt(decryptMem, key);
  std::string memory(decryptMem.data());
  std::vector<std::string> list;
  finding(list, memory);
  if (list.size() > 0) {
    std::stringstream ss;
    ss << "Key=" << std::hex << static_cast<int>(key) << std::dec;
    data.push_back(ss.str());
    for (std::string val : list) {
      data.push_back(val);
    }
  }
}

void Finder::findXorValues(std::vector<std::string> &data, std::vector<char> const &mem, std::vector<unsigned char> key,
                              std::function<void(std::vector<std::string> &, std::string const &)> finding){
  std::vector<char> decryptMem = mem;
  Decrypt::xorDecrypt(decryptMem, key);
  std::string memory(decryptMem.data());
  std::vector<std::string> list;
  finding(list, memory);
  if (list.size() > 0) {
    std::stringstream ss;
    if (key.size() > 1)
      ss << "Key=" << std::hex << static_cast<int>(key[0]) << static_cast<int>(key[1]) << std::dec;
    else
      ss << "Key=" << std::hex << static_cast<int>(key[0]) << std::dec;
    data.push_back(ss.str());
    for (std::string val : list) {
      data.push_back(val);
    }
  }
}

void Finder::findMailCiphered(std::vector<std::string> &data, std::vector<char> const &mem) {
  std::vector<std::pair<std::vector<unsigned char>, long>>      analyseX;
  std::vector<std::pair<unsigned char, long>>      analyseC;
  long maxC = Finder::findCaesar(mem, analyseC);
  long maxX = Finder::findXor(mem, analyseX);
  if (maxC > maxX) {
    data.push_back("Caesar>>");
    for (size_t i = 0; i < analyseC.size(); i++) {
      if (analyseC[i].second == maxC) {
        findCaesarValues(data, mem, analyseC[i].first, Finder::mail);
      }
    }
  } else if (maxX > maxC) {
    data.push_back("Xor>>");
    for (size_t i = 0; i < analyseX.size(); i++) {
      if (analyseX[i].second == maxX) {
        findXorValues(data, mem, analyseX[i].first, Finder::mail);
      }
    }
  } else {
    data.push_back("Caesar>>");
    for (size_t i = 0; i < analyseC.size(); i++) {
      if (analyseC[i].second == maxC) {
        findCaesarValues(data, mem, analyseC[i].first, Finder::mail);
      }
    }
    data.push_back("Xor>>");
    for (size_t i = 0; i < analyseX.size(); i++) {
      if (analyseX[i].second == maxX) {
        findXorValues(data, mem, analyseX[i].first, Finder::mail);
      }
    }
  }
}

void Finder::findIPCiphered(std::vector<std::string> &data, std::vector<char> const &mem) {
  std::vector<std::pair<std::vector<unsigned char>, long>>      analyseX;
  std::vector<std::pair<unsigned char, long>>      analyseC;
  long maxC = Finder::findCaesar(mem, analyseC);
  long maxX = Finder::findXor(mem, analyseX);
  if (maxC > maxX) {
    data.push_back("Caesar>>");
    for (size_t i = 0; i < analyseC.size(); i++) {
      if (analyseC[i].second == maxC) {
        findCaesarValues(data, mem, analyseC[i].first, Finder::ip);
      }
    }
  } else if (maxX > maxC) {
    data.push_back("Xor>>");
    for (size_t i = 0; i < analyseX.size(); i++) {
      if (analyseX[i].second == maxX) {
        findXorValues(data, mem, analyseX[i].first, Finder::ip);
      }
    }
  } else {
    data.push_back("Caesar>>");
    for (size_t i = 0; i < analyseC.size(); i++) {
      if (analyseC[i].second == maxC) {
        findCaesarValues(data, mem, analyseC[i].first, Finder::ip);
      }
    }
    data.push_back("Xor>>");
    for (size_t i = 0; i < analyseX.size(); i++) {
      if (analyseX[i].second == maxX) {
        findXorValues(data, mem, analyseX[i].first, Finder::ip);
      }
    }
  }
}

void Finder::findPhoneCiphered(std::vector<std::string> &data, std::vector<char> const &mem) {
  std::vector<std::pair<std::vector<unsigned char>, long>>      analyseX;
  std::vector<std::pair<unsigned char, long>>      analyseC;
  long maxC = Finder::findCaesar(mem, analyseC);
  long maxX = Finder::findXor(mem, analyseX);
  if (maxC > maxX) {
    data.push_back("Caesar>>");
    for (size_t i = 0; i < analyseC.size(); i++) {
      if (analyseC[i].second == maxC) {
        findCaesarValues(data, mem, analyseC[i].first, Finder::phone);
      }
    }
  } else if (maxX > maxC) {
    data.push_back("Xor>>");
    for (size_t i = 0; i < analyseX.size(); i++) {
      if (analyseX[i].second == maxX) {
        findXorValues(data, mem, analyseX[i].first, Finder::phone);
      }
    }
  } else {
    data.push_back("Caesar>>");
    for (size_t i = 0; i < analyseC.size(); i++) {
      if (analyseC[i].second == maxC) {
        findCaesarValues(data, mem, analyseC[i].first, Finder::phone);
      }
    }
    data.push_back("Xor>>");
    for (size_t i = 0; i < analyseX.size(); i++) {
      if (analyseX[i].second == maxX) {
        findXorValues(data, mem, analyseX[i].first, Finder::phone);
      }
    }
  }
}
