//
// Created by ilyas on 29/04/17.
//

#include "Decrypt.hpp"

Decrypt::Decrypt() {

}

Decrypt::~Decrypt() {

}

void Decrypt::xorDecrypt(std::vector<char> &data, std::vector<unsigned char> const &key){
  unsigned int n = 0;
  for (unsigned int i = 0; i < data.size(); i++) {
    char tmp = data[i] ^ static_cast<char>(key[n]);
    if ((data[i] = tmp) == 0) {
      data[0] = '\0';
      break;
    }
    ++n;
    if (n >= key.size())
      n = 0;
  }
}

void Decrypt::caesarDecrypt(std::vector<char> &data, unsigned char const &key) {
  for (unsigned int i = 0; i < data.size(); i++) {
    int tmp = static_cast<int>(data[i]) + static_cast<int>(key);
    if (tmp > 255)
      tmp -= 256;
    if ((data[i] = static_cast<char>(tmp)) == 0) {
      data[0] = '\0';
      break;
    }
  }
}
