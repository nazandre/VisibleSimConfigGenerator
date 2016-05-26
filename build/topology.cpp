#include "topology.hpp"

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
