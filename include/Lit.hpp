#ifndef LIT_HPP
#define LIT_HPP

#include <string>

/*
  Linking phase structures
*/

struct Expression;
struct Args;

/* Datatypes */

enum DataType {
  Expr, String, Int, Float, Bool, Null
};

struct DefinedString {
  char* value;
  unsigned int size;
};

/* Data representation */

union Data {
  int intval;
  float floatval;
  DefinedString str;
  bool boolean;
};

/* Expression */

struct Args {
  Expression* argv;
  unsigned int argc;
};

struct Expression {
  Data data;
  Args args;
  DataType type;
  std::string tostr;
};

/* Functions */

/* Creates a defined string from a std::string */
DefinedString create_defined_string(std::string &str);

/* Creates a clone of an expression */
Expression clone_expression(Expression const& expr);

/* Copies e data (and type) into e2 */
void copy_value(Expression *e,Expression *e2);

/* Frees expression */
void free_expression(Expression &expr);

#endif
