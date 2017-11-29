#include "Lit.hpp"

/* Functions */

/* Creates a defined string from a std::string */
DefinedString create_defined_string(std::string &str) {
  DefinedString s;
  s.size = str.size();
  s.value = new char[s.size + 1];
  std::string::iterator it = str.begin();;
  for(unsigned i = 0;i < s.size;i++,it++) s.value[i] = *it;
  s.value[s.size] = '\0';
  return s;
}

/* Creates a clone of an expression */
Expression clone_expression(Expression const& expr) {
  Expression into;
  into.type = expr.type;
  into.data = expr.data;
  into.tostr = expr.tostr;
  into.args.argc = expr.args.argc;
  into.args.argv = new Expression[expr.args.argc];
  for(unsigned int i = 0;i < expr.args.argc;i++) {
    into.args.argv[i] = clone_expression(expr.args.argv[i]);
  }
  return into;
}

void copy_value(Expression *e,Expression *e2) {
  e2->data = e->data;
  e2->type = e->type;
}

/* Frees expression */
void free_expression(Expression &expr) {
  for(unsigned int i = 0;i < expr.args.argc;i++) {
    if(expr.type == String) {
      delete[] expr.data.str.value;
    }
    free_expression(expr.args.argv[i]);
  }
  if(expr.args.argc != 0) {
    delete[] expr.args.argv;
  }
}
