#include "process_input.h"
#include <cctype>
#include <fmt/core.h>
#include <iostream>

InputParser::InputParser() {}
InputParser::~InputParser() {}

void InputParser::readInput() {
  std::cout << "Enter an equation be calculated: ";
  std::getline(std::cin, input);
  walkString(input);
}

void InputParser::parseInput() {
  if (input.empty())
    return;
}

void InputParser::printEquation() {
  std::string equation =
      fmt::format("Equation: {}{}{}", getLhs(), getOperand(), getRhs());
  std::cout << equation << std::endl;
}

void InputParser::walkString(std::string str) {
  // 1. Loop through string
  for (int i = 0; i < str.length(); i++) {
    // 2. Read each char until we hit an operand (+-*/) and save that to num1
    // 3. Add operand to operand prop
    // 4. Continue to read until whitespace char and save to num2
  }
}
