#include "Stack.hpp"

Stack* push(Stack* s,Expression* val) { // Pushes new stack
  Stack* ss = new Stack;
  ss->next = s;
  ss->value = val;
  return ss;
}

Stack* pop(Stack* s,Stack* until) { // Pops last stack
  if(s == until) return until;
  if(s == 0) return 0;
  Stack* ss = s->next;
  delete s;
  return pop(ss,until);
}

void free_stack(Stack* s) { // Frees stack
  while((s = pop(s)));
}

Expression* search(Stack *s,std::string const& name) { // Searches expression through stack
  if(s == 0) {
    return 0;
  } else {
    if(s->value == 0) return search(s->next,name);
    return (s->value->tostr == name) ? s->value : search(s->next,name);
  }
}
