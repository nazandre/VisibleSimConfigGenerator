#ifndef LATTICE_H_
#define LATTICE_H_

#include <string>
#include <vector>
#include "node.hpp"
#include "vector3D.hpp"

typedef enum Dimension_t {
  ONE_D_DIMENSION = 1,
  TWO_D_DIMENSION = 2,
  THREE_D_DIMENSION = 3,
  NUM_D_DIMENSIONS = 4
} Dimension;

typedef enum LatticeType_t
{
  UNKNOWN_LATTICE = -1,
  SQUARE_LATTICE = 0,
  HEXAGONAL_LATTICE = 1,
  SIMPLE_CUBIC_LATTICE = 2,
  FACE_CENTERED_CUBIC_LATTICE = 3,
  NUM_LATTICE_TYPES = 4
} LatticeType;

class Lattice {

public:
  LatticeType type;
  Vector3D size; // grid size (3D)
  Node ** grid;
   
  Lattice();
  Lattice(Vector3D& s, LatticeType t);
  Lattice(const Lattice &l);
  virtual ~Lattice();

  static std::string typeShortName[];
  static std::string typeFullName[];
  static LatticeType getType(std::string t);

  virtual Dimension getDimension() = 0;
  
  bool isIn(Vector3D &p); 
  int getIndex(Vector3D &p);
  void insert(Node* n,Vector3D &p);
  Node *getNode(Vector3D &p);
  
  bool isFree(Vector3D &p);
  Vector3D getMiddle();

  std::vector<Vector3D> getNeighborCells(Node *n);

  virtual std::vector<Vector3D> getRelativeConnectivity(Vector3D &p) = 0;
};

// Hexgaonal (H) Lattice
class HLattice : public Lattice {

public:
  HLattice();
  HLattice(Vector3D& s);
  HLattice(const HLattice &l);
  ~HLattice();

  Dimension getDimension();
  
  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};

// Simple Cubic (SC) Lattice (okay for Square (S) Lattice as well)
class SCLattice : public Lattice {

public:
  std::vector<Vector3D> nCells;
  
  SCLattice();
  SCLattice(Vector3D& s);
  SCLattice(const SCLattice &l);
  ~SCLattice();

  Dimension getDimension();
  
  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};

// Face-Centered Cubic (FCC) Lattice
class FCCLattice : public Lattice {

public:
  
  FCCLattice();
  FCCLattice(Vector3D& s);
  FCCLattice(const FCCLattice &l);
  ~FCCLattice();

  Dimension getDimension();
  
  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};


#endif
