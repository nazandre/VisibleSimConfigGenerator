#ifndef LATTICE_H_
#define LATTICE_H_

#include <string>
#include <vector>
#include <cmath>

#include "node.hpp"
#include "vector3D.hpp"

typedef enum Dimension_t {
  UNKNOWN_DIMENSION = -1,
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
  Lattice(Vector3D&s, LatticeType t);
  Lattice(const Lattice &l);
  virtual ~Lattice();

  static std::string typeShortName[];
  static std::string typeFullName[];
  static LatticeType getType(std::string t);

  virtual Dimension getDimension() = 0;
  static Dimension getDimension(LatticeType t);
  
  bool isIn(Vector3D &p); 
  int getIndex(Vector3D &p);
  void insert(Node* n,Vector3D &p);
  Node *getNode(Vector3D &p);
  
  bool isFree(Vector3D &p);
  Vector3D getMiddle();

  std::vector<Vector3D> getNeighborCells(Node *n);
  virtual std::vector<Vector3D> getRelativeConnectivity(Vector3D &p) = 0;

  static Vector3D getSize(LatticeType t, int n);
  static Vector3D getSize(LatticeType t, const Vector3D& s);
};

// 2D Lattice
class Lattice2D : public Lattice {

public:
  Lattice2D();
  Lattice2D(Vector3D& s, LatticeType t);
  Lattice2D(const Lattice2D &l);
  virtual ~Lattice2D();

  Dimension getDimension();
  
  virtual std::vector<Vector3D> getRelativeConnectivity(Vector3D &p) = 0;
};

// 3D Lattice
class Lattice3D : public Lattice {

public:
  Lattice3D();
  Lattice3D(Vector3D& s, LatticeType t);
  Lattice3D(const Lattice2D &l);
  virtual ~Lattice3D();

  Dimension getDimension();
  
  virtual std::vector<Vector3D> getRelativeConnectivity(Vector3D &p) = 0;
};

// Square (S) Lattice
class SLattice : public Lattice2D {
  std::vector<Vector3D> nCells;
public:
  SLattice();
  SLattice(Vector3D& s);
  SLattice(const SLattice &l);
  ~SLattice();

  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};

// Hexgaonal (H) Lattice
class HLattice : public Lattice2D {

public:
  HLattice();
  HLattice(Vector3D& s);
  HLattice(const HLattice &l);
  ~HLattice();

  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};

// Simple Cubic (SC) Lattice (okay for Square (S) Lattice as well)
class SCLattice : public Lattice3D {

public:
  std::vector<Vector3D> nCells;
  
  SCLattice();
  SCLattice(Vector3D& s);
  SCLattice(const SCLattice &l);
  ~SCLattice();
  
  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};

// Face-Centered Cubic (FCC) Lattice
class FCCLattice : public Lattice3D {

public:
  
  FCCLattice();
  FCCLattice(Vector3D& s);
  FCCLattice(const FCCLattice &l);
  ~FCCLattice();
  
  std::vector<Vector3D> getRelativeConnectivity(Vector3D &p);
};

#endif
