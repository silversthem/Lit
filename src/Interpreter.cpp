#include "Interpreter.hpp"

/* Protected methods */

void Interpreter::build_function(Expression& expr) {
  if(expr.args.argc > 1) {
    defs[expr.args.argv[0].tostr] = &expr;
    log("# Registering function " + expr.args.argv[0].tostr);
  }
}

void Interpreter::build_assignation(Expression& expr) {
  if(expr.args.argc > 1) {
    eval(expr.args.argv[1]); // Constant value, evaluated once
    log("# Registering " + expr.args.argv[0].tostr + " as " + expr.args.argv[1].tostr);
    lets[expr.args.argv[0].tostr] = &expr.args.argv[1];
  }
}

/* Class behavior */

Interpreter::Interpreter() {
  stack = new Stack;
}
Interpreter::~Interpreter() {
  free_stack(stack);
}

/* Public methods */

void Interpreter::add_function(std::string const& name,Function f,bool const& eArgs) {
  ExtFunction ef = {f,eArgs};
  stl[name] = ef;
  log("... Adding c function " + name);
}

void Interpreter::call(Expression &expr) {
  /* C Style function */
  std::map<std::string,ExtFunction>::iterator it = stl.find(expr.tostr);
  if(it != stl.end()) { // C function
    /* Evaluating arguments */
    if(it->second.evalArgs) {
      for(unsigned int i = 0;i < expr.args.argc;i++) {
        eval(expr.args.argv[i]);
      }
    }
    /* Calling function */
    log("  <> Calling c function : " + expr.tostr)
    (*(it->second.func))(this,&expr.args,&expr);
  } else {
      /* Function/Constant */
      std::map<std::string,Expression*>::iterator it2 = defs.find(expr.tostr);
      if(it2 != defs.end()) { // Function
        log("  <> Function " + expr.tostr);
        Expression* fn = it2->second;
        Stack* start = stack;
        log("  Argc : " << fn->args.argc - 2 << " (provided " << expr.args.argc << ")");
        if((fn->args.argc - 2) == expr.args.argc) { // Exactly enough parameters
          /* Pushing parameters */
          for(unsigned int i = 0;i < expr.args.argc;i++) {
            eval(expr.args.argv[i]);
          }
          for(unsigned int i = 0;i < expr.args.argc;i++) {
            expr.args.argv[i].tostr = fn->args.argv[i+1].tostr; // Naming parameters
            stack = push(stack,&expr.args.argv[i]);
            log("# Pushing " << expr.args.argv[i].tostr << " to stack");
          }
          /* Copying Expression from definition */
          Expression f = clone_expression(fn->args.argv[fn->args.argc - 1]);
          /* Evaluating */
          log(".Calling function : ");
          eval(f);
          log("..");
          /* Output */
          copy_value(&f,&expr);
          log("    = " << f.type << " " << f.data.intval);
          /* Poping parameters */
          free_expression(f);
          stack = pop(stack,start);
        } else { // Not exactly enough parameters
          // @TODO
        }
      } else {
        it2 = lets.find(expr.tostr);
        if(it2 != lets.end()) { // Constant
          copy_value(it2->second,&expr); // Output
        }
      }
  }
}

void Interpreter::eval(Expression &expr) { // Evaluates expression
  log("<---- Evalutating " + expr.tostr);
  if(expr.type == Expr) { // Function
    /* Langage keywords */
    if(expr.tostr == "main") { // Running program
      for(unsigned int i = 0;i < expr.args.argc;i++) {
        eval(expr.args.argv[i]);
      }
    }
    else if(expr.tostr == "define") { // Definition
      log("--- Function definition ---");
      build_function(expr);
      log("---");
    } else if(expr.tostr == "let") { // Assignation
      log("--- Assignation definition ---");
      build_assignation(expr);
      log("---");
    } else { // Function call
      log("*** Function call ***");
      call(expr);
      log("***");
    }
    /* Search in stack */
    Expression *stack_value = search(stack,expr.tostr);
    if(stack_value != 0) { // Stack value
      log("  <> From stack " + expr.tostr);
      copy_value(stack_value,&expr);
    }
  }
  log("---->");
}
