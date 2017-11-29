#include "Parser.hpp"

/* Creating a Lit */
LitAST* create_Lit() {
  LitAST* l = new LitAST;
  l->type = ASTNodeType::Element;
  return l;
}

LitAST* attach(LitAST *l,ASTNodeType const& t) {
  LitAST *c = create_Lit();
  c->type = t;
  (l->args).push_back(c);
  return c;
}

bool is_number(char c) {
  return (c >= '0' && c <= '9');
}

/* Check if character is whitespace */
bool is_whitespace(char c) {
  return (c == '\n' || c == '\t' || c == '\r' || c == ' ');
}

/* Parsing text into a Lit tree by moving iterator recursively */
std::string::iterator parse_from_it(std::string::iterator const& fromIt,std::string::iterator const& endIt,LitAST *root,LitAST *current) {
  if(fromIt == endIt) return endIt;
  if(current == 0) { // Initializating call
    current = root;
  }
  std::string::iterator it = fromIt;
  bool nextArg = false;
  for(;it != endIt;) {
    switch (*it) {
      case '(': { // New block
        LitAST *block = attach(current);
        do {
          it++;
        } while(is_whitespace(*it) && it != endIt);
        it = parse_from_it(it,endIt,root,block);
        it++;
        nextArg = true;
        break;
      }
      case ')': { // End of current block
        return it; // Returning to parent block
        break;
      }
      case ';': { // Comment
        while(*it != '\n' && it != endIt) it++;
        break;
      }
      case '"': { // Start of string literal element
        it++;
        bool guard = false;
        LitAST* str = attach(current,ASTNodeType::StringLitteral);
        while(it != endIt && !(*it == '"' && !guard)) {
          if(*it == '\\') {
            if(guard) {
              str->keyword += '\\';
            }
            guard = !guard;
          } else {
            str->keyword += *it;
          }
          it++;
        }
        if(it != endIt) it++;
        break;
      }
      default: // Default case : Number literal, whitespace or character
        if(is_whitespace(*it)) { // Whitespace
          while(is_whitespace(*it)) it++;
          nextArg = true;
        } else { // Argument
          if(nextArg) { // New Argument
            nextArg = false;
            attach(current);
            if(is_number(*it)) { // Potential number literal
              current->args.back()->type = ASTNodeType::IntLitteral;
            }
          }
          /* Adding current character to AST */
          LitAST *c = (current->args.size() == 0) ? // Selecting right keyword
            current : current->args.back();
          if(!is_number(*it)) {
            if(*it == '.' && c->type == ASTNodeType::IntLitteral) {
              c->type = ASTNodeType::FloatLitteral;
            } else {
              c->type = ASTNodeType::Element;
            }
          }
          c->keyword += *it;
          it++;
        }
        break;
    }
  }
  return endIt;
}

/* Turning code into a Lit tree */
LitAST* parse(std::string &str) {
  LitAST *l = create_Lit();
  l->keyword = "main";
  parse_from_it(str.begin(),str.end(),l,l);
  return l;
}

/* Prints a Lit */
void print_Lit(LitAST* root,int const& lvl) {
  for(int i = 0;i < lvl;i++) {
    std::cout << "\t";
  }
  if(root->type == ASTNodeType::StringLitteral) std::cout << "[string] ";
  if(root->type == ASTNodeType::IntLitteral) std::cout << "[int] ";
  if(root->type == ASTNodeType::FloatLitteral) std::cout << "[float] ";
  std::cout << "* " << root->keyword << std::endl;
  for(auto element : root->args) {
    print_Lit(element,lvl+1);
  }
}

/* Frees a Lit tree */
void free_Lit(LitAST *root) {
  for(auto element : root->args) {
    free_Lit(element);
  }
  delete root;
}
