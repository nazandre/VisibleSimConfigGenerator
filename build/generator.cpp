#include <iostream>
#include <random>
#include "generator.hpp"
#include "utils.hpp"
#include "color.hpp"

using namespace std;

//#define GENERATION_DEBUG

Generator::Generator(Configuration &c, Topology t) : configuration(c),
						     topology(t) {}

Generator::Generator(const Generator &g) :  configuration(g.configuration),
					    topology(g.topology) {}

Generator::~Generator() {}

void Generator::generate() {

#ifdef GENERATION_DEBUG
  cout << "grid: " << configuration.lattice->size << endl;
#endif
  
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

  cerr << "Mixing nodes id..." << endl;
  int n = configuration.getSize();
  mixNodes(n*n);
}

void Generator::generateRandom() {
  int id = 1;
  int n = topology.parameter;
  Vector3D &defaultColor = configuration.robot.getDefaultColor();
  Vector3D mColor = defaultColor;
  Vector3D middle = configuration.getMiddle();
  Node *node;
  bool inserted;
  // Uniformly-distributed integer random number generator that produces non-deterministic random numbers. 
  random_device r;
  int seed = r();
  default_random_engine e1(seed);
  vector<Node*> freeNodes;
  
  cerr << "Generating a random configuration of size " << n << "..." << endl;

  if (configuration.colored) {
    mColor = Color::getRandom();
  }
  node = new Node(id,middle,mColor);
  //cout << "insert at " << middle.x << " " << middle.y << " " << middle.z << endl; 
  configuration.insert(node,middle);
  freeNodes.push_back(node);
  id++;

  for (int i = 0; i < n-1; i++) {
    inserted = false;
    while(!inserted) {
      if (freeNodes.size() == 0) {
	cerr << "ERROR: Lattice not big enough to contain " << n << " modules!" << endl;
	return;
      }
      // Produces random integer values rid, uniformly distributed on the closed interval [0, i],
      uniform_int_distribution<int> uniform_dist1(0, freeNodes.size()-1);
      int rid = uniform_dist1(e1);
      node = freeNodes[rid];
      //node = configuration.getNode(rid);
      vector<Vector3D> positions = configuration.getEmptyNeighborCells(node);
#ifdef GENERATION_DEBUG
      cout << "Neighbors of " << node->position << ":";
      for (int k = 0; k < (int)positions.size(); k++) {
	cout << " " << positions[k];
      }
      cout << endl;
#endif
      
      if (positions.size() == 0) {
	freeNodes.erase(freeNodes.begin()+rid);
	continue;
      }
      
      uniform_int_distribution<int> uniform_dist2(0, positions.size()-1);
      int rnc = uniform_dist2(e1);
      Vector3D& position = positions[rnc];
#ifdef GENERATION_DEBUG
      cout << "Insert "<< i <<  " at " << position << endl;
      cout << endl;
#endif
      if (configuration.isFree(position)) {
	if (configuration.colored) {
	  mColor = Color::getRandom();
	}
	node = new Node(id,position,mColor);
	configuration.insert(node,position);
	freeNodes.push_back(node);
	id++;
	inserted = true;
      }
    }
  }
}

void Generator::generateBall() {
  int r = topology.parameter;
  int id = 1;
  Vector3D middle = configuration.getMiddle();
  Vector3D &defaultColor = configuration.robot.getDefaultColor();
  Vector3D mColor = defaultColor;

  if (configuration.colored) {
    mColor = Color::getColor(color(0));
  }
  Node *node = new Node(id,middle,mColor);

  cerr << "Generating a ball configuration of radius " << r << "..." << endl;
  configuration.insert(node,middle);
  id++;
  // r rounds, add max possible number of neighbors at every existing module
  for (int i = 0; i < r; i++) {
    int currentSize = configuration.getSize();
    if (configuration.colored) {
      mColor = Color::getColor(color((i+1)%NUM_COLORS));
    }
    for (int j = 0; j < currentSize; j++) {
      node = configuration.getNode(j);
      vector<Vector3D> positions = configuration.getNeighborCells(node);
      for (int k = 0; k < (int)positions.size(); k++) {
	Vector3D &position = positions[k];
	if (configuration.isFree(position)) {
	  node = new Node(id,position,mColor);
	  configuration.insert(node,position);
	  id++;
	}
      }
    }
  }
}

void Generator::generateLine() {
  int n = topology.parameter;
  Vector3D &defaultColor = configuration.robot.getDefaultColor();
  Vector3D mColor = defaultColor;
  int id = 1;
  Node *node;
  Vector3D position = configuration.getMiddle();
  
  position.x = 0;
 
  cerr << "Generating a line configuration of length " << n << "..." << endl;

  if (configuration.colored) {
    mColor = Color::getRandom();
  }
  node = new Node(id,position,mColor);
  configuration.insert(node,position);
  id++;
  for (int i = 1; i < n; i++) {
    position.x++;
#ifdef GENERATION_DEBUG
    cout << "insert at " << position << "..." << endl;
#endif
    if (!configuration.lattice->isIn(position)) {
      cerr << "ERROR: Lattice too small to create an horizontal line of " << n << " modules!" << endl;
      exit(EXIT_FAILURE);
    }
    if (configuration.colored) {
      mColor = Color::getRandom();
    }
    node = new Node(id,position,mColor);
    configuration.insert(node,position);
    id++;
  }
}


void Generator::mixNodes(int p) {
  random_device r;
  int seed = r();
  default_random_engine e1(seed);
  uniform_int_distribution<int> uniform_dist1(0, configuration.getSize()-1);

  // swap two nodes 
  for (int i = 0; i < p; i++) {
    int id1, id2;
    do {
      id1 = uniform_dist1(e1);
      id2 = uniform_dist1(e1);
    } while (id1 == id2);
    configuration.swapNodes(id1,id2);
  }
}
