#include "calculator.h"
#include <cctype>
#include <exception>
#include <fmt/core.h>
#include <iostream>
#include <memory>
#include <string>

int main() {
  std::unique_ptr<Calculator> calc = std::make_unique<Calculator>();
  std::string input;
  std::cout << "Please input an equation to be calculated."
               "\r\nExample: 4*9"
            << std::endl;

  std::getline(std::cin, input);

  try {
    calc->evaluateExpression(input);
    std::cout << "Expression: " << calc->getExpression() << std::endl;
    std::cout << "Result: " << calc->getResult() << std::endl;
  } catch (const std::exception &ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }

  return 0;
}
