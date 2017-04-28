//
// Created by ilyas on 29/04/17.
//

#ifndef PLAZZA_DECRYPT_HPP
#define PLAZZA_DECRYPT_HPP


#include <vector>

class Decrypt {

private:
  Decrypt();
  ~Decrypt();

public:
  static void  xorDecrypt(std::vector<char> &data, std::vector<unsigned char> const &key);
  static void  caesarDecrypt(std::vector<char> &data, unsigned char const &key);


};


#endif //PLAZZA_DECRYPT_HPP
