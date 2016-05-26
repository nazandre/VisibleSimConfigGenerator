#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <string>
#include "vector3D.hpp"

class Arguments {
public:
  std::string output;
  std::string robot;
  std::string topology;
  std::string parameter;
  std::string size;
  
  Arguments();
  Arguments(int argc, char *argv[]);
  Arguments(const Arguments &a);
  ~Arguments();

  void readOne(std::string &s, int &argc, char **argv[]);
  
  void help();
  
};

#endif
