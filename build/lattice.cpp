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
  if (size.x == 0 ||
      size.y == 0 ||
      size.z == 0) {
    cerr << "ERROR: Incorrect lattice size (size in any direction can not be null)." << endl;
  }
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

/****** 2D Lattice Class ******/

Lattice2D::Lattice2D() : Lattice() {}
Lattice2D::Lattice2D(Vector3D& s, LatticeType t) : Lattice(s,t) {}
Lattice2D::Lattice2D(const Lattice2D &l) : Lattice(l) {}
Lattice2D::~Lattice2D() {}

Dimension Lattice2D::getDimension() {
  return TWO_D_DIMENSION;
}

/****** 3D Lattice Class ******/

Lattice3D::Lattice3D() : Lattice() {}
Lattice3D::Lattice3D(Vector3D& s, LatticeType t) : Lattice(s,t) {}
Lattice3D::Lattice3D(const Lattice2D &l) : Lattice(l) {}
Lattice3D::~Lattice3D() {}

Dimension Lattice3D::getDimension() {
  return THREE_D_DIMENSION;
}

/****** Square Lattice Class ******/

SLattice::SLattice() : Lattice2D() {}

SLattice::SLattice(Vector3D& s) : Lattice2D(s, SQUARE_LATTICE) {
  nCells.push_back(Vector3D(1,0,0));
  nCells.push_back(Vector3D(-1,0,0));
  nCells.push_back(Vector3D(0,1,0));
  nCells.push_back(Vector3D(0,-1,0));
}

SLattice::SLattice(const SLattice &l) : Lattice2D(l) {
  nCells = l.nCells;
}

SLattice::~SLattice() {}

vector<Vector3D> SLattice::getRelativeConnectivity(Vector3D &p) {
  return nCells;
}

/****** Vertical Hexgonal Lattice Class ******/

HLattice::HLattice() : Lattice2D() {}

HLattice::HLattice(Vector3D& s) : Lattice2D(s, HEXAGONAL_LATTICE) {}

HLattice::HLattice(const HLattice &l) : Lattice2D(l) {}

HLattice::~HLattice() {}

vector<Vector3D> HLattice::getRelativeConnectivity(Vector3D &p) {
  vector<Vector3D> nCells;

  nCells.push_back(Vector3D(1,0,0));
  nCells.push_back(Vector3D(-1,0,0));

  nCells.push_back(Vector3D(0,0,1));
  nCells.push_back(Vector3D(0,0,-1));
  
  if (EVEN(p.z)) {
    nCells.push_back(Vector3D(1,0,1));
    nCells.push_back(Vector3D(1,0,-1));
  } else {
    nCells.push_back(Vector3D(-1,0,1));
    nCells.push_back(Vector3D(-1,0,-1));
  }

  return nCells;
}

/****** Simple Cubic Lattice Class ******/

SCLattice::SCLattice() : Lattice3D() {}

SCLattice::SCLattice(Vector3D& s) : Lattice3D(s, SIMPLE_CUBIC_LATTICE) {
  nCells.push_back(Vector3D(1,0,0));
  nCells.push_back(Vector3D(-1,0,0));
  nCells.push_back(Vector3D(0,0,1));
  nCells.push_back(Vector3D(0,0,-1));
  nCells.push_back(Vector3D(0,1,0));
  nCells.push_back(Vector3D(0,-1,0));
}

SCLattice::SCLattice(const SCLattice &l) : Lattice3D(l) {
  nCells = l.nCells;
}

SCLattice::~SCLattice() {}

vector<Vector3D> SCLattice::getRelativeConnectivity(Vector3D &p) {
  return nCells;
}

/****** Face-Centered Cubic Lattice Class ******/

FCCLattice::FCCLattice() : Lattice3D() {}

FCCLattice::FCCLattice(Vector3D& s) : Lattice3D(s, SIMPLE_CUBIC_LATTICE) {}

FCCLattice::FCCLattice(const FCCLattice &l) : Lattice3D(l) {}

FCCLattice::~FCCLattice() {}

vector<Vector3D> FCCLattice::getRelativeConnectivity(Vector3D &p) {
  vector<Vector3D> nCells;
  
  if (ODD(p.z)) {
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
