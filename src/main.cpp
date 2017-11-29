#include "IO.hpp"
#include "Parser.hpp"
#include "Builder.hpp"
#include "STL.hpp"

int main(int argc,char** argv) {
  Interpreter interpreter;
  /* Loading standard library */
  import(interpreter);
  /* Code to interpret */
  std::string codeStr;
  /* Interpreting Lit code from a file */
  if(argc == 2) {
    codeStr = file_to_str(argv[1]);
  } else {
    codeStr = file_to_str("examples/test.lit");
  }
  /* Parsing */
  LitAST *l = parse(codeStr);
  //print_Lit(l);
  /* Building */
  Expression expr;
  expr = build_expression(l);
  /* Interpreting */
  interpreter.eval(expr);
  /* Freeing ressources */
  free_expression(expr);
  free_Lit(l);
  return 0;
}
