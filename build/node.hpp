#ifndef NODE_H_
#define NODE_H_

#include "vector3D.hpp"

class Node {
public:
  int id;
  Vector3D position;
  Vector3D color;

  Node();
  Node(int i, Vector3D &position, Vector3D &color);
  Node(const Node &n);
  ~Node();
};

#endif
