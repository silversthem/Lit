#include <iostream>
#include "AST.hpp"

/* Creating a Lit */
LitAST* create_Lit();

/* Creates an attached Lit tree */
LitAST* attach(LitAST *l,ASTNodeType const& t = ASTNodeType::Element);

/* Check if character is whitespace */
bool is_whitespace(char c);

/* Parsing text into a Lit tree by moving iterator recursively */
std::string::iterator parse_from_it(std::string::iterator const& fromIt,std::string::iterator const& endIt,LitAST *root,LitAST *current = 0);

/* Turning code into a Lit tree */
LitAST* parse(std::string &str);

/* Prints a Lit */
void print_Lit(LitAST* root,int const& lvl = 0);

/* Frees a Lit tree */
void free_Lit(LitAST *root);
