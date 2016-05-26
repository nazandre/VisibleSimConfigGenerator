#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "configuration.hpp"
#include "topology.hpp"

class Generator {

public:
  Configuration &configuration;
  Topology topology;

  //Generator();
  Generator(Configuration &c, Topology t);
  Generator(const Generator &g);
  ~Generator();

  void generate();
  void generateRandom();
  void generateBall();
  void generateLine();

  void mixNodes(int p);
};

#endif
