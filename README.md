# Lit
Lit is a lisp like interpreted language to embed into your c++ programs.
It can serve as a scripting language, but can also be used to build interfaces or initialize values in your program.
## How to use
Lit's syntax is very simple, all expressions follow the same pattern :
`(instructiong arg1 arg2 arg3...)`

For example : 
`(+ 2 2)` will return 4 (Note that the `+` function is variadic, meaning it can take as many arguments as you need).

Comments are denoted by a `;` and stop at endline.
## Current version
Currently Lit is a pet project of mine, therefore not very developped (or well crafted) yet, but I plan on updating it frequently and adding features to make it suitable for real life C++ applications.
### Roadmap :
- Types :
  - ~~Default types (int,float,string,bool,expr)~~
  - User types
  - Methods on types
  - Overloading functions on types
- Optimizations :
  - Tail recursion
  - Memoisation
- STL :
  - IO
  - Math
  - Network
  - Threads
- Data structures :
  - arrays/vectors
  - lists/stacks/piles
  - trees
  - graphs
