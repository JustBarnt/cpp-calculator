#pragma once

#include <string>

class Calculator {
public:
  Calculator(std::string &result, std::string &expression)
      : result(result), expression(expression) {}
  void evaluateExpression(const std::string_view &expr);

public:
  std::string &getResult() const noexcept { return result; };
  std::string &getExpression() const noexcept { return expression; };

private:
  std::string &result;
  std::string &expression;
};
