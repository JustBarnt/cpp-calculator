#pragma once

#include <cctype>
#include <fmt/core.h>
#include <string>

class Calculator {
public:
  Calculator() noexcept = default;
  ~Calculator() noexcept = default;

public:
  double parseExpression(const std::string &expr, size_t &pos);
  double parseTerm(const std::string &expr, size_t &pos);
  double parseFactor(const std::string &expr, size_t &pos);
  double parseNumber(const std::string &expr, size_t &pos);
  void evaluateExpression(const std::string &expr);
  void skipWhitespace(const std::string &expr, size_t &pos);

public:
  std::string getResult() const;
  std::string getExpression() const;

private:
  std::string result;
  std::string expression;
};
