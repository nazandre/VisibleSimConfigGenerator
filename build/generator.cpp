#include <iostream>
#include <random>
#include "generator.hpp"
#include "utils.hpp"

using namespace std;

#define GENERATION_DEBUG

Generator::Generator(Configuration &c, Topology t) : configuration(c),
						     topology(t) {}

Generator::Generator(const Generator &g) :  configuration(g.configuration),
					    topology(g.topology) {}

Generator::~Generator() {}

void Generator::generate() {
  switch(topology.type) {
  case RANDOM_TOPOLOGY:
    generateRandom();
    break;
  case BALL_TOPOLOGY:
    generateBall();
    break;
  case LINE_TOPOLOGY:
    generateLine();
    break;
  default:
    cerr << "ERROR: Unable to generate unknown topology type "
	 << topology.type << endl;
  }

  int n = configuration.getSize();
  mixNodes(n*n);
}

void Generator::generateRandom() {
  int id = 1;
  int n = topology.parameter;
  Vector3D middle = configuration.getMiddle();
  Node *node;
  bool inserted;
  // Uniformly-distributed integer random number generator that produces non-deterministic random numbers. 
  random_device r;
  int seed = r();
  default_random_engine e1(seed);

  cerr << "Generating random configuration of size " << n << "..." << endl;
  
  node = new Node(id,middle);
  //cout << "insert at " << middle.x << " " << middle.y << " " << middle.z << endl; 
  configuration.insert(node,middle);
  id++;

  for (int i = 0; i < n-1; i++) {
    // Produces random integer values rid, uniformly distributed on the closed interval [0, i],
    uniform_int_distribution<int> uniform_dist1(0, i);
    inserted = false;
    while(!inserted) {
      int rid = uniform_dist1(e1);
      node = configuration.getNode(rid);
      vector<Vector3D> positions = configuration.getNeighborCells(node);
#ifdef GENERATION_DEBUG
      cout << "Neighbors of " << node->position << ":";
      for (int k = 0; k < (int)positions.size(); k++) {
	cout << " " << positions[k];
      }
      cout << endl;
#endif
      uniform_int_distribution<int> uniform_dist2(0, positions.size()-1);
      int rnc = uniform_dist2(e1);
      Vector3D& position = positions[rnc];
#ifdef GENERATION_DEBUG
      cout << "Insert "<< i <<  " at " << position << endl;
      cout << endl;
#endif
      if (configuration.isFree(position)) {
	node = new Node(id,position);
	configuration.insert(node,position);
	id++;
	inserted = true;
      }
    }
  }
}

void Generator::generateBall() {
  int r = topology.parameter;
  int id = 1;
  //Utils::notImplementedYet();
  Vector3D middle = configuration.getMiddle();
  Node *node = new Node(id,middle);

  cerr << "Generating ball configuration of radius " << r << "..." << endl;
  configuration.insert(node,middle);
  id++;
  // r rounds, add max possible number of neighbors at every existing module
  for (int i = 0; i < r; i++) {
    int currentSize = configuration.getSize();
    for (int j = 0; j < currentSize; j++) {
      node = configuration.getNode(j);
      vector<Vector3D> positions = configuration.getNeighborCells(node);
      for (int k = 0; k < (int)positions.size(); k++) {
	Vector3D &position = positions[k];
	if (configuration.isFree(position)) {
	  node = new Node(id,position);
	  configuration.insert(node,position);
	  id++;
	}
      }
    }
  }
}

void Generator::generateLine() {
  int n = topology.parameter;
  Utils::notImplementedYet();
  cerr << "Generating line configuration of length " << n << "..." << endl;
}


void Generator::mixNodes(int p) {
  random_device r;
  int seed = r();
  default_random_engine e1(seed);
  uniform_int_distribution<int> uniform_dist1(0, configuration.getSize()-1);
  
  for (int i = 0; i < p; i++) {
    int id1, id2;
    do {
      id1 = uniform_dist1(e1);
      id2 = uniform_dist1(e1);
    } while (id1 == id2);
    configuration.swapNodes(id1,id2);
  }
}
