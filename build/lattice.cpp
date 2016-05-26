#include <iostream>
#include <cstdlib>
#include "lattice.hpp"

using namespace std;

#define EVEN(x) (x%2 == 1)
#define ODD(x) (x%2 == 0)

/****** Lattice Class ******/

std::string Lattice::typeShortName[] = {"s","h","sc","fcc"};
std::string Lattice::typeFullName[] = {"Square","Hexagonal","Simple-Cubic","Face-Centered Cubic"};

Lattice::Lattice() {
  grid = NULL;
}

Lattice::Lattice(Vector3D &s, LatticeType t) {
  type = t;
  size = s;
  grid = new Node*[size.x*size.y*size.z]{NULL};
}

Lattice::Lattice(const Lattice &l) {
  type = l.type;
  size = l.size;
  grid = NULL;
}

Lattice::~Lattice() {
  delete [] grid;
}

LatticeType Lattice::getType(std::string t) {
  for(int i = 0; i < NUM_LATTICE_TYPES; i++) {
    if(t == typeShortName[i] || t == typeFullName[i]) {
      return LatticeType(i);
    }
  }
  return UNKNOWN_LATTICE;
}

int Lattice::getIndex(Vector3D &p) {
  int index = p.x + (p.z*size.y + p.y)*size.x;
  //cout << "index: " << index << "(/total = " << size.x*size.y*size.z << ")" << endl;
  return index;
}

void Lattice::insert(Node* n,Vector3D &p) {
  grid[getIndex(p)] = n;
}

Node* Lattice::getNode(Vector3D &p) {
  return grid[getIndex(p)];
}

Vector3D Lattice::getMiddle() {
  return size/2;
}

bool Lattice::isFree(Vector3D &p) {
  return (getNode(p) == NULL);
}

bool Lattice::isIn(Vector3D &p) {
  return (p.x >= 0 && p.x < size.x &&
	  p.y >= 0 && p.y < size.y &&
	  p.z >= 0 && p.z < size.z);
}


vector<Vector3D> Lattice::getNeighborCells(Node *n) {
  vector<Vector3D> l;
  vector<Vector3D> nCells = getRelativeConnectivity(n->position); // depends on p and lattice type
  for (vector<Vector3D>::iterator it=nCells.begin();
       it != nCells.end(); ++it) {
    Vector3D v = n->position + *it;
    if (isIn(v)) {
	l.push_back(v);
    }
  }
  return l;
}

/****** Hexgonal Lattice Class ******/

HLattice::HLattice() {}

HLattice::HLattice(Vector3D& s) : Lattice(s, HEXAGONAL_LATTICE) {
  size.z = 1; // 2D lattices ...
}

HLattice::HLattice(const HLattice &l) : Lattice(l) {}

HLattice::~HLattice() {}

vector<Vector3D> HLattice::getRelativeConnectivity(Vector3D &p) {
  vector<Vector3D> nCells;

  nCells.push_back(Vector3D(1,0,0));
  nCells.push_back(Vector3D(-1,0,0));

  nCells.push_back(Vector3D(0,1,0));
  nCells.push_back(Vector3D(0,-1,0));
  
  if (EVEN(p.y)) {
    nCells.push_back(Vector3D(1,1,0));
    nCells.push_back(Vector3D(1,-1,0));
  } else {
    nCells.push_back(Vector3D(-1,1,0));
    nCells.push_back(Vector3D(-1,-1,0));
  }

  return nCells;
}

Dimension HLattice::getDimension() {
  return TWO_D_DIMENSION;
}

/****** Simple Cubic Lattice Class ******/

SCLattice::SCLattice() {}

SCLattice::SCLattice(Vector3D& s) : Lattice(s, SIMPLE_CUBIC_LATTICE) {
  nCells.push_back(Vector3D(1,0,0));
  nCells.push_back(Vector3D(-1,0,0));
  nCells.push_back(Vector3D(0,0,1));
  nCells.push_back(Vector3D(0,0,-1));
  nCells.push_back(Vector3D(0,1,0));
  nCells.push_back(Vector3D(0,-1,0));
}

SCLattice::SCLattice(const SCLattice &l) : Lattice(l) {
  nCells = l.nCells;
}

SCLattice::~SCLattice() {
}

Dimension SCLattice::getDimension() {
  return THREE_D_DIMENSION;
}

vector<Vector3D> SCLattice::getRelativeConnectivity(Vector3D &p) {
  return nCells;
}

/****** Face-Centered Cubic Lattice Class ******/

FCCLattice::FCCLattice() {}

FCCLattice::FCCLattice(Vector3D& s) : Lattice(s, SIMPLE_CUBIC_LATTICE) {}

FCCLattice::FCCLattice(const FCCLattice &l) : Lattice(l) {}

FCCLattice::~FCCLattice() {}

Dimension FCCLattice::getDimension() {
  return THREE_D_DIMENSION;
}

vector<Vector3D> FCCLattice::getRelativeConnectivity(Vector3D &p) {
  vector<Vector3D> nCells;
  
  if (EVEN(p.z)) {
    // z + 1
    nCells.push_back(Vector3D(-1,-1,1));
    nCells.push_back(Vector3D(-1,0,1));
    nCells.push_back(Vector3D(0,0,1));
    nCells.push_back(Vector3D(0,-1,1));
    // z
    nCells.push_back(Vector3D(-1,0,0));
    nCells.push_back(Vector3D(1,0,0));
    nCells.push_back(Vector3D(0,-1,0));
    nCells.push_back(Vector3D(0,1,0));
    // z - 1
    nCells.push_back(Vector3D(-1,-1,-1));
    nCells.push_back(Vector3D(-1,0,-1));
    nCells.push_back(Vector3D(0,0,-1));
    nCells.push_back(Vector3D(0,-1,-1));
  } else {
    // z + 1
    nCells.push_back(Vector3D(0,0,1));
    nCells.push_back(Vector3D(0,1,1));
    nCells.push_back(Vector3D(1,0,1));
    nCells.push_back(Vector3D(1,1,1));
    // z
    nCells.push_back(Vector3D(-1,0,0));
    nCells.push_back(Vector3D(1,0,0));
    nCells.push_back(Vector3D(0,-1,0));
    nCells.push_back(Vector3D(0,1,0));
    // z - 1
    nCells.push_back(Vector3D(0,0,-1));
    nCells.push_back(Vector3D(0,1,-1));
    nCells.push_back(Vector3D(1,0,-1));
    nCells.push_back(Vector3D(1,1,-1));
  }
  return nCells;
}
