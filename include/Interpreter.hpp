#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "Stack.hpp"
#include <map>

#define DEBUG 0

#if DEBUG == 1
  #define log(event) std::cout << event << std::endl;
#else
  #define log(event)
#endif

class Interpreter;

typedef void (*Function) (Interpreter*,Args*,Expression*);

/* External functions */

struct ExtFunction {
  Function func;
  bool evalArgs;
};

/* Interpreter */

class Interpreter {
protected:
  std::map<std::string,ExtFunction> stl; // Default functions
  std::map<std::string,Expression*> defs; // Program definitions
  std::map<std::string,Expression*> lets; // Program assignations
  Stack *stack; // Stack
  /* Adding language function definition reference */
  void build_function(Expression& expr);
  /* Adding language constant definition reference */
  void build_assignation(Expression& expr);
public:
  /* Class behavior */
  Interpreter();
  ~Interpreter();
  /* Adding c function */
  void add_function(std::string const& name,Function f,bool const& eArgs = true);
  /* Calling a function */
  void call(Expression &expr);
  /* Interpreting function */
  void eval(Expression &expr);
};

#endif
