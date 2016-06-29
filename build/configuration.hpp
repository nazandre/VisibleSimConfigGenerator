#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <vector>
#include <iostream>

#include "vector3D.hpp"
#include "robot.hpp"
#include "node.hpp"
#include "lattice.hpp"

class Configuration {

public:
  Robot robot;
  std::vector<Node*> nodes; 
  Lattice *lattice;
  bool colored;

  Configuration();
  Configuration(Robot &r, Vector3D& s, bool c);
  Configuration(const Configuration &c);
  ~Configuration();

  int getSize();
  Node* getNode(int i);
  Node* getNode(Vector3D& p);
  void insert(Node* n, Vector3D& p);
  bool isFree(Vector3D& p);
  Vector3D getMiddle();

  std::vector<Vector3D> getNeighborCells(Node *n);
  std::vector<Vector3D> getEmptyNeighborCells(Node *n);
  
  void swapNodes(int i, int j);
  
  void createLattice(Vector3D& s);

  std::ostream& exportToVisibleSim(std::ostream &output);
  
};

#endif
