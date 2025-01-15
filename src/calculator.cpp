#include "calculator.h"
#include <cctype>
#include <fmt/core.h>
#include <stdexcept>
#include <string>

namespace {
using ctraits = std::char_traits<char>;
bool is_space(char c) noexcept { return std::isblank(ctraits::to_int_type(c)); }
// Helpers to quickly check if chararact at position is a digit
bool is_digit(char c) noexcept { return std::isdigit(ctraits::to_int_type(c)); }
} // namespace

namespace {
double parseTerm(const std::string_view &expr, size_t &pos);
double parseExpression(const std::string_view &expr, size_t &pos);
double parseFactor(const std::string_view &expr, size_t &pos);
double parseNumber(const std::string_view &expr, size_t &pos);
size_t skipWhitespace(const std::string_view &expr, size_t &pos);

size_t skipWhitespace(const std::string_view &expr, size_t &pos) {
  while (pos < expr.size() && is_space(expr[pos])) {
    ++pos;
  }
  return pos;
}

double parseNumber(const std::string_view &expr, size_t &pos) {
  pos = skipWhitespace(expr, pos);

  std::string numStr;
  while (pos < expr.size() && is_digit(expr[pos])) {
    numStr.push_back(expr[pos]);
    ++pos;
  }

  if (numStr.empty())
    throw std::runtime_error("Expected a number but found none");

  return std::stod(numStr);
}

double parseFactor(const std::string_view &expr, size_t &pos) {
  pos = skipWhitespace(expr, pos);
  if (pos >= expr.size())
    throw std::runtime_error(fmt::format(
        "Unexpected end of expression: Error found at: {}", expr.substr(pos)));

  if (expr[pos] == '(') {
    ++pos;
    double value = parseExpression(expr, pos);

    pos = skipWhitespace(expr, pos);
    if (pos >= expr.size() || expr[pos] != ')') {
      throw std::runtime_error("Missing closing parathesis");
    }
    ++pos;
    return value;
  } else if (is_digit(static_cast<unsigned char>(expr[pos]))) {
    return parseNumber(expr, pos);
  } else {
    throw std::runtime_error(
        fmt::format("Unexpected character in factor: '{}'", expr[pos]));
  }
}

double parseTerm(const std::string_view &expr, size_t &pos) {
  double value = parseFactor(expr, pos);
  while (true) {
    pos = skipWhitespace(expr, pos);

    if (pos >= expr.size())
      break;

    char op = expr[pos];
    if (op == '*' || op == '/') {
      ++pos;
      double rhs = parseFactor(expr, pos);

      if (op == '*') {
        value *= rhs;
      } else {
        if (rhs == 0.0) {
          throw std::runtime_error("Division by zero");
        }
        value /= rhs;
      }
    } else {
      break;
    }
  }
  return value;
}

double parseExpression(const std::string_view &expr, size_t &pos) {
  double value = parseTerm(expr, pos);

  while (true) {
    pos = skipWhitespace(expr, pos);

    if (pos >= expr.size())
      break;

    char op = expr[pos];

    if (op == '+' || op == '-') {
      ++pos;
      double rhs = parseTerm(expr, pos);

      if (op == '+')
        value += rhs;
      else
        value -= rhs;
    } else {
      break;
    }
  }
  return value;
}
} // namespace

void Calculator::evaluateExpression(const std::string_view &expr) {
  size_t pos = 0;
  expression = expr;
  double value = parseExpression(expr, pos);

  pos = skipWhitespace(expr, pos);
  if (pos < expr.size())
    throw std::runtime_error("Unexpexted extra input after valid expression");

  result = std::to_string(value);
}
