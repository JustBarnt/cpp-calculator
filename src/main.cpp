#include <iostream>

int main() {
  std::string input;
  std::cout << "Please input an equation to be calculated."
               "\r\nExample: 4*9"
            << std::endl;

  std::getline(std::cin, input);

  // RUN CODE FROM process_input.cpp

  return 0;
}
