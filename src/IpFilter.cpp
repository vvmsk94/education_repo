#include "IpFilter.h"
#include <algorithm>
#include <cstring>
IP_Filter::IP_Filter() {
  status = 0;
  std::memset(pointsIndex, 0, sizeof(pointsIndex));
  std::ifstream in("ip_filter.tsv");
  if (in.is_open()) {
    is_file_exist = true;
    while (std::getline(in, line)) {
      line = line.substr(0, line.find_first_of('\t'));
      int ii = 0;
      for (int i = 0; i < line.size(); i++) {
        if (line[i] == '.') {
          pointsIndex[ii] = i;
          ii++;
        }
      }
      octets.first = atoi(line.substr(0, pointsIndex[0]).c_str());
      octets.second =
          atoi(line.substr(pointsIndex[0] + 1, pointsIndex[1]).c_str());
      octets.third =
          atoi(line.substr(pointsIndex[1] + 1, pointsIndex[2]).c_str());
      octets.fourth =
          atoi(line.substr(pointsIndex[2] + 1, line.size()).c_str());

      VecStr.push_back(octets);
    }

  } else {
    is_file_exist = false;
    std::cout << "File doesn't exist ..." << std::endl;
  }
  in.close();
}

void IP_Filter::survey() {
  if (is_file_exist == false)
    return;
  std::cout
      << "\t\t\tHello\n"
      << "You have successfully opened the ip_filter.tsv file and you can:\n"
      << "1.\t" << "Filter to first octer\n"
      << "2.\t" << "Filter to first and second\n"
      << "3.\t" << "Filter one any octer\n"
      << "\n"
      << "\n"
      << "\n"
      << "Enter your choice" << "\n";

  int choose = 0;
  int octet = 0;
  int octet2 = 0;
  std::cin >> choose;
  switch (choose) {
  case 1:
    std::cout << "Your choice Filter to first octer \n" << "Enter octet:";
    std::cin >> octet;
    find_first_byte(octet);
    break;
  case 2:
    std::cout << "Your choice Filter to first and second\n"
              << "Enter first octet:\n";
    std::cin >> octet;
    std::cout << "Enter second octet:\n";
    std::cin >> octet2;
    find_first_and_second_byte(octet, octet2);
    break;
  case 3:
    std::cout << "Your choice Filter one any octer\n" << "Enter octet:";
    std::cin >> octet;
    find_any_byte(octet);
    break;
  default:
    break;
  }
}

void IP_Filter::find_first_byte(int f_byte) {
  if (is_file_exist == false)
    return;
  for (auto el : VecStr) {
    if (el.first == f_byte) {
      status = 1;
      std::cout << el.first << "." << el.second << "." << el.third << "."
                << el.fourth << std::endl;
    }
  }
  if (status != 1)
    std::cout << "Byte doesn't exist";
  else
    status = 0;
}

void IP_Filter::find_first_and_second_byte(int f_byte, int sec_byte) {
  if (is_file_exist == false)
    return;
  for (auto el : VecStr) {
    if (el.first == f_byte && el.second == sec_byte) {
      status = 2;
      std::cout << el.first << "." << el.second << "." << el.third << "."
                << el.fourth << std::endl;
    }
  }
  if (status != 2)
    std::cout << "Bytes doesn't exist";
  else
    status = 0;
}

void IP_Filter::find_any_byte(int byte) {
  if (is_file_exist == false)
    return;
  for (auto el : VecStr) {
    if (el.first == byte || el.second == byte || el.third == byte ||
        el.fourth == byte) {
      status = 3;
      std::cout << el.first << "." << el.second << "." << el.third << "."
                << el.fourth << std::endl;
    }
  }
  if (status != 3)
    std::cout << "Byte doesn't exist";
  else
    status = 0;
}
