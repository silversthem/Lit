#include "Builder.hpp"

Expression build_expression(LitAST* input) {
  Expression expr;
  expr.args.argc = 0;
  expr.tostr = input->keyword;
  switch (input->type) {
    case ASTNodeType::Element: { // Linking keyword from AST to function
      expr.args.argc = input->args.size();
      expr.args.argv = new Expression[input->args.size()];
      expr.type = Expr;
      /* Parsing args */
      for(unsigned int i = 0;i < input->args.size();i++) {
        expr.args.argv[i] = build_expression(input->args[i]);
      }
      break;
    }
    case ASTNodeType::StringLitteral: { // Linking from a string litteral
      expr.type = String;
      expr.data.str = create_defined_string(input->keyword);
      break;
    }
    case ASTNodeType::IntLitteral: { // Linking from a int litteral
      expr.type = Int;
      expr.data.intval = std::stoi(input->keyword);
      break;
    }
    case ASTNodeType::FloatLitteral: { // Linking from a float litteral
      expr.type = Float;
      expr.data.floatval = std::stof(input->keyword);
      break;
    }
  }
  return expr;
}
