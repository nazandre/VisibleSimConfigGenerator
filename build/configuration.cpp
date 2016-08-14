#include <iostream>
#include <cstdlib>
#include "utils.hpp"
#include "configuration.hpp"
#include "color.hpp"

using namespace std;

Configuration::Configuration() {
  lattice = NULL;
  colored = false;
}

Configuration::Configuration(Robot &r, Vector3D &s, bool c) {
  robot = r;
  lattice = NULL;
  createLattice(s);
  colored = c;
}

Configuration::Configuration(const Configuration &c) {
  cerr << "ERROR: Configuration copy constructor not yet properly implemented!" << endl;
  exit(EXIT_FAILURE);
  robot = c.robot;
  lattice = NULL; // TODO
  //instantiateLattice();
  colored = c.colored;
}

Configuration::~Configuration() {
  for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    Node *n = *it;
    delete n;
  }
  delete lattice;
}

int Configuration::getSize() {
  return nodes.size();
}

Node* Configuration::getNode(int i) {
  return nodes[i];
}

void Configuration::insert(Node* n, Vector3D& p) {
  nodes.push_back(n);
  lattice->insert(n,p);
}

bool Configuration::isFree(Vector3D& p) {
  return lattice->isFree(p);
}

Vector3D Configuration::getMiddle() {
  return lattice->getMiddle();
}

vector<Vector3D> Configuration::getNeighborCells(Node *n) {
  return lattice->getNeighborCells(n);
}

vector<Vector3D> Configuration::getEmptyNeighborCells(Node *n) {
  vector<Vector3D> neighborCells = getNeighborCells(n);
  vector<Vector3D>::iterator it;

  for (it = neighborCells.begin(); it != neighborCells.end();) {
    if (!isFree(*it)) {
      it=neighborCells.erase(it);
    } else {
      it++;
    }
  }
  
  return neighborCells;
}

void Configuration::swapNodes(int i, int j) {
  Node *tmpn = nodes[i];
  nodes[i] = nodes[j];
  nodes[j] = tmpn;
  /*
  int tmpi = nodes[i].id;
  nodes[i].id = nodes[j].id;
  nodes[j].id = tmpi;*/
}

void Configuration::createLattice(Vector3D& s) {
  switch(robot.type) {
  case(BLINKYBLOCKS_ROBOT) :
    lattice = new SCLattice(s);
    break;
  case(SMART_BLOCKS_ROBOT) :
    lattice = new SLattice(s);
    break;
  case(CATOMS2D_ROBOT) :
    lattice = new HLattice(s);
    break;
  case(CATOMS3D_ROBOT) :
    lattice = new FCCLattice(s);
    break;
  default:
    cerr << "ERROR: Unknown lattice type." << endl;
  }
}

ostream& Configuration::exportToVisibleSim(ostream &output) {
  Vector3D &robotVSFormatSize = robot.getTypeVSFormatSize();
  Vector3D &robotCompFormatSize = robot.getTypeCompFormatSize();
  Vector3D &latticeSize = lattice->size;
  Vector3D &defaultColor = robot.getDefaultColor();
  
  //target(angle azimut,angle elevation, distance) 
  int angleAzimut = 0;
  int angleElevation = 25;
  double coef = 115./100.;

  Vector3D sceneSize = robotCompFormatSize * latticeSize;
  Vector3D midPoint = sceneSize/2;
  
  int distance = max(max(sceneSize.x, sceneSize.y), sceneSize.z+midPoint.z)*coef;
  
  cerr << "exporting to VisibleSim..." << endl;

  output << "<?xml version=\"1.0\" standalone=\"no\" ?>" << endl;
  
  // header
  output << "<world gridSize=\"" << latticeSize.getString() << "\">" << endl;
  output << "  <camera target=\"" << midPoint.getString() << "\" directionSpherical=\"" << angleAzimut << "," << angleElevation << "," << distance << "\" angle=\"45\"/>" << endl;
  output << "  <spotlight target=\"" << midPoint.getString() << "\" directionSpherical=\"" << angleAzimut << "," << angleElevation << "," << distance << "\" angle=\"30\"/>" << endl;
  
  // module list
  output << "  <blockList color=\""
	 << defaultColor.getString()
	 << "\" blocksize=\""
	 << robotVSFormatSize.getString()
	 << "\">" << endl;
  for (int i = 0; i < getSize(); i++) {
    Vector3D &p = nodes[i]->position;

    output << "    <block position=\"" << p.getString() << "\""
	   << " color=\"" << nodes[i]->color.getString() << "\""
	   << "/>" << endl;
  }
  output << "  </blockList>" << endl;
  output << "</world>" << endl;
  return output;
}
