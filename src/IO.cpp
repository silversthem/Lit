#include "IO.hpp"

std::string file_to_str(std::string const& fname) {
  std::ifstream f(fname);
  std::string r;
  char c;
  while(f.get(c)) r += c;
  return r;
}
