#include "topology.hpp"

#include <cassert>

using namespace std;

string Topology::typeShortName[] = {"r","b","l"};
string Topology::typeFullName[] = {"random","networkball","line"};
string Topology::parameterName[] = {"size","radius","length"};

Topology::Topology() {}

Topology::Topology(TopologyType t, int p) {
  type = t;
  parameter = p;
}

Topology::Topology(const Topology &t) {
  type = t.type;
  parameter = t.parameter;
}

Topology:: ~Topology() {}

TopologyType Topology::getType(std::string t) {
  for(int i = 0; i < NUM_TOPOLOGIES; i++) {
    if(t == typeShortName[i] || t == typeFullName[i]) {
      return TopologyType(i);
    }
  }
  return UNKNOWN_TOPOLOGY;
}

Vector3D Topology::getLatticeSize(LatticeType t, double occupancyRatio) {
  switch(type) {
  case LINE_TOPOLOGY:
    // minimum x-size:
    // n
    return Vector3D(parameter,1,1);
  case BALL_TOPOLOGY:
    {
      // minimum size in all direction:
      // 2*radius + 1
      int c = 2*parameter+1;
      Vector3D s = Vector3D(c,c,c);
      return Lattice::getSize(t,s);
    }
  case RANDOM_TOPOLOGY:
    {
      // minimum size in all direction
      // 1 + (square/cubic root of n)
      
      // ratio = #cells / n
      // #cells = ratio * n
      // side = sqrt or ^(1./3.) 
      int cells = 1./occupancyRatio*parameter;
      return Lattice::getSize(t,cells);
    }
    break;
  default:
    cerr << "WARNING: Unknown lattice type." << endl;
    //assert(false);
  }
  return Vector3D(0,0,0);
}

void Topology::checkSize(LatticeType t, Vector3D& s) {
  //if (
  Vector3D size = Lattice::getSize(t,s);
  
  switch(type) {
  case LINE_TOPOLOGY:
    if (parameter > size.x) {
      cerr << "ERROR: lattice width (x axis) should be greater than "
	   << parameter
	   << endl;
      assert(false);
    }
  case BALL_TOPOLOGY:
    {
      // minimum size in all direction:
      // 2*radius + 1
      int c = 2*parameter+1;
      if (size.x < c ||
	  (size.y == s.y && size.y < c) ||
	  (size.z == s.z && size.z < c) ) {
	cerr << "ERROR: lattice side should be greater than 2*radius + 1 = " << c << endl;
	assert(false);
      }
    }
  case RANDOM_TOPOLOGY:
    {
      int cells = size.x*size.y*size.z;
      if (parameter > cells) {
	cerr << "ERROR: lattice volume (#cells) should be greater than "
	     << parameter << "."
	     << "There is only " << cells
	     << " in the lattice of size " << size 
	     << endl;
	assert(false);
      }
    }
    break;
  default:
    cerr << "WARNING: Unknown lattice type." << endl;
    //assert(false);
  }
 
}
