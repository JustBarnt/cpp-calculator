#pragma once

#include <string>
class InputParser {
public:
  InputParser();
  ~InputParser();

  void readInput();
  void parseInput();
  void walkString(std::string str);
  void printEquation();

  int getLhs() const;
  int getRhs() const;
  int getOperand() const;

private:
  std::string input;
  // TODO: Turn these into arrays to allow more complex arithmatic

  int lhs;
  int rhs;
  char op;
};
