#include "node.hpp"

Node::Node() {}

Node::Node(int i, Vector3D &p) {
  id = i;
  position = p;
}

Node::Node(const Node &n) {
  id = n.id;
  position = n.position;
}

Node::~Node() {}
