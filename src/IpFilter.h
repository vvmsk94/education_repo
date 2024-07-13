#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Octets {
  int first;
  int second;
  int third;
  int fourth;
};

class IP_Filter {
public:
  IP_Filter();

  void survey();
  void find_first_byte(int f_byte);
  void find_first_and_second_byte(int f_byte, int sec_byte);
  void find_any_byte(int byte);

private:
  std::string line;
  int pointsIndex[3];
  std::vector<Octets> VecStr;
  Octets octets;
  bool is_file_exist;
  int status;
};
