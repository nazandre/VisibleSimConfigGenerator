#include "node.hpp"

Node::Node() {}

Node::Node(int i, Vector3D &p, Vector3D &c) {
  id = i;
  position = p;
  color = c;
}

Node::Node(const Node &n) {
  id = n.id;
  position = n.position;
  color = n.color;
}

Node::~Node() {}
