//
// Created by ilyas on 29/04/17.
//

#include "Decrypt.hpp"

Decrypt::Decrypt() {

}

Decrypt::~Decrypt() {

}

void Decrypt::xorDecrypt(std::vector<char> &data, std::vector<unsigned char> const &key){
  int n = 0;
  for (int i = 0; i < data.size(); i++) {
    if ((data[i] ^= key[n]) == 0) {
      data[0] = '\0';
      break;
    }
    ++n;
    if (n >= key.size())
      n = 0;
  }
}

void Decrypt::caesarDecrypt(std::vector<char> &data, unsigned char const &key) {
  for (int i = 0; i < data.size(); i++) {
    int tmp = static_cast<int>(data[i]) + static_cast<int>(key);
    if (tmp > 255)
      tmp -= 255;
    if ((data[i] = static_cast<char>(tmp)) == 0) {
      data[0] = '\0';
      break;
    }
  }
}