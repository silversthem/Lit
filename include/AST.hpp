#ifndef AST_HPP
#define AST_HPP

/*
  Parsing phase (AST)
*/

#include <string>
#include <vector>

/* Types of nodes */
enum ASTNodeType {
  Element,StringLitteral,IntLitteral,FloatLitteral
};

/* Lit Tree Structure */
struct LitAST {
  ASTNodeType type;
  std::string keyword;
  std::vector<LitAST*> args;
};

#endif
