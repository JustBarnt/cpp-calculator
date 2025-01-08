#pragma once

#include <string>
#include <vector>

// Allowed Token Types in our equation
enum class TokenType { Number, Operator, LeftParen, RightParen };

struct Token {
  TokenType type;
  std::string value;
};
