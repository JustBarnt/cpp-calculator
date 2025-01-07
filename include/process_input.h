#pragma once

#include <string>
class InputParser {
public:
  // Member Functions
  std::string ParseInput(std::string cinput);

private:
  // TODO: Turn these into arrays to allow more complex arithmatic
  int left_int;
  int right_int;
  char operand;
};
