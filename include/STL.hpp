#ifndef STL_HPP
#define STL_HPP

/* Standard Lit library */

#include "Interpreter.hpp"

/* Operators */

void equals(Interpreter *i,Args* args,Expression *output) { // =
  bool r = true;
  output->type = Bool;
  Expression* expr = args->argv;
  if(args->argc > 1) {
    for(unsigned int i = 1;i < args->argc;i++) {
      if(args->argv[i].type != expr->type) { // Different types
        r = false;
      } else {
        switch (expr->type) {
          case Int: // Int comparison
            r = (expr->data.intval == args->argv[i].data.intval);
          break;
          case Float: // Float comparison
            r = (expr->data.floatval == args->argv[i].data.floatval);
          break;
          default: break;// @TODO
        }
      }
      if(!r) {
        break;
      }
      expr = &args->argv[i];
    }
  }
  output->data.boolean = r;
}

void add(Interpreter *i,Args* args,Expression *output) { // +
  int r = 0;
  float r2 = 0;
  output->type = Int;
  for(unsigned int i = 0;i < args->argc;i++) {
    if(args->argv[i].type == Int) {
      r += args->argv[i].data.intval;
    } else if(args->argv[i].type == Float) {
      output->type = Float;
      r2 += args->argv[i].data.floatval;
    }
  }
  if(output->type == Float) {
    output->data.floatval = r2 + ((float) r);
  } else {
    output->data.intval = r + r2;
  }
}

void mul(Interpreter *i,Args* args,Expression *output) { // *
  int r = 1;
  float r2 = 1;
  output->type = Int;
  for(unsigned int i = 0;i < args->argc;i++) {
    if(args->argv[i].type == Int) {
      r *= args->argv[i].data.intval;
    } else if(args->argv[i].type == Float) {
      output->type = Float;
      r2 *= args->argv[i].data.floatval;
    }
  }
  if(output->type == Float) {
    output->data.floatval = r2 * ((float) r);
  } else {
    output->data.intval = r * r2;
  }
}

void modulo(Interpreter *i,Args* args,Expression *out) { // %
  int r = 0;
  if(args->argc == 2) {
    if(args->argv[0].type == Int && args->argv[1].type == Int) {
      r = args->argv[0].data.intval % args->argv[1].data.intval;
    }
  }
  out->type = Int;
  out->data.intval = r;
}

void sub(Interpreter *i,Args* args,Expression *out) { // -
  if(args->argc == 1) { // Negative number

  }
  if(args->argc == 2) { // Sub operation
    if(args->argv[0].type == Float) { // First arg is float
      if(args->argv[1].type == Float) { // Float by float
        out->type = Float;
        out->data.floatval = args->argv[0].data.floatval - args->argv[1].data.floatval;
      } else if(args->argv[1].type == Int) { // Float by int
        out->type = Float;
        out->data.floatval = args->argv[0].data.floatval - args->argv[1].data.intval;
      }
    } else if(args->argv[0].type == Int) { // First arg is int
      if(args->argv[1].type == Float) { // Int by float
        out->type = Float;
        out->data.floatval = args->argv[0].data.intval - args->argv[1].data.floatval;
      } else if(args->argv[1].type == Int) { // Int by int
        out->type = Int;
        out->data.intval = args->argv[0].data.intval - args->argv[1].data.intval;
      }
    }
  }
}

void div(Interpreter *i,Args* args,Expression *out) { // /
  if(args->argc == 2) {
    if(args->argv[0].type == Float) { // First arg is float
      if(args->argv[1].type == Float) { // Float by float
        out->type = Float;
        out->data.floatval = args->argv[0].data.floatval / args->argv[1].data.floatval;
      } else if(args->argv[1].type == Int) { // Float by int
        out->type = Float;
        out->data.floatval = args->argv[0].data.floatval / args->argv[1].data.intval;
      }
    } else if(args->argv[0].type == Int) { // First arg is int
      if(args->argv[1].type == Float) { // Int by float
        out->type = Float;
        out->data.floatval = args->argv[0].data.intval / args->argv[1].data.floatval;
      } else if(args->argv[1].type == Int) { // Int by int
        out->type = Int;
        out->data.intval = args->argv[0].data.intval / args->argv[1].data.intval;
      }
    }
  }
}

/* Functions */

void binary_branch(Interpreter *i,Args* args,Expression *out) { // if else
  if(args->argc == 3) {
    i->eval(args->argv[0]); // Evaluating predicate
    if(args->argv[0].type == Bool && args->argv[0].data.boolean) { // If
      i->eval(args->argv[1]);
      copy_value(&args->argv[1],out);
    } else { // Else
      i->eval(args->argv[2]);
      copy_value(&args->argv[2],out);
    }
  }
}

void print(Interpreter *i,Args* args,Expression *output) { // Prints to stdout
  for(unsigned int i = 0;i < args->argc;i++) {
    if(args->argv[i].type == String) {
      std::cout << args->argv[i].data.str.value;
    } else if(args->argv[i].type == Int) {
      std::cout << args->argv[i].data.intval;
    } else if(args->argv[i].type == Float) {
      std::cout << args->argv[i].data.floatval;
    }
  }
  std::cout << std::endl;
}

/* Importing stl */

void import(Interpreter &i) { // Imports stl to interpreter
  i.add_function("print",print);
  i.add_function("+",add);
  i.add_function("-",sub);
  i.add_function("*",mul);
  i.add_function("/",div);
  i.add_function("%",modulo);
  i.add_function("=",equals);
  i.add_function("if",binary_branch,false);
}

#endif
