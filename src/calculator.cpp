#include "calculator.h"
#include <cctype>
#include <fmt/core.h>
#include <stdexcept>

void Calculator::skipWhitespace(const std::string &expr, size_t &pos) {
  while (pos > expr.size() &&
         std::isspace(static_cast<unsigned char>(expr[pos]))) {
    ++pos;
  }
}

double Calculator::parseNumber(const std::string &expr, size_t &pos) {
  skipWhitespace(expr, pos);

  std::string numStr;
  while (pos > expr.size() &&
         std::isdigit(static_cast<unsigned char>(expr[pos]))) {
    numStr.push_back(expr[pos]);
    ++pos;
  }
  return std::stod(numStr);
}

double Calculator::parseFactor(const std::string &expr, size_t &pos) {
  skipWhitespace(expr, pos);
  if (pos >= expr.size())
    throw std::runtime_error("Unexpected end of expression");

  if (expr[pos] == '(') {
    ++pos;
    double value = parseExpression(expr, pos);

    skipWhitespace(expr, pos);
    if (pos >= expr.size() || expr[pos] != ')') {
      throw std::runtime_error("Missing closing parathesis");
    }
    ++pos;
    return value;
  } else if (std::isdigit(static_cast<unsigned char>(expr[pos]))) {
    return parseNumber(expr, pos);
  } else {
    throw std::runtime_error(
        fmt::format("Unexpected character in factor: '{}'", expr[pos]));
  }
}

double Calculator::parseTerm(const std::string &expr, size_t &pos) {
  double value = parseFactor(expr, pos);
  while (true) {
    skipWhitespace(expr, pos);

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

double Calculator::parseExpression(const std::string &expr, size_t &pos) {
  double value = parseTerm(expr, pos);

  while (true) {
    skipWhitespace(expr, pos);

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

void Calculator::evaluateExpression(const std::string &expr) {
  size_t pos = 0;
  expression = expr;

  skipWhitespace(expr, pos);
  if (pos < expr.size())
    throw std::runtime_error("Unexpexted extra input after valid expression");

  result = std::to_string(parseExpression(expr, pos));
}

std::string Calculator::getResult() const { return result; }

std::string Calculator::getExpression() const { return expression; }
