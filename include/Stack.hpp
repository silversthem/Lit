#ifndef STACK_HPP
#define STACK_HPP

#include "Lit.hpp"

/* Stack definition */

struct Stack {
  Stack *next;
  Expression* value;
  Stack() : next(0),value(0) {}
};

/* Stack manipulation */

Stack* push(Stack* s,Expression* val = 0);

Stack* pop(Stack* s,Stack* until = 0);

void free_stack(Stack* s);

Expression* search(Stack *s,std::string const& name);

#endif
