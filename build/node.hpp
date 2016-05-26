#ifndef NODE_H_
#define NODE_H_

#include "vector3D.hpp"

class Node {
public:
  int id;
  Vector3D position;

  Node();
  Node(int i, Vector3D &position);
  Node(const Node &n);
  ~Node();
};

#endif
