#ifndef TOPOLOGY_H_
#define TOPOLOGY_H_

#include <string>

typedef enum TopologyType_t
{
  UNKNOWN_TOPOLOGY = -1,
  RANDOM_TOPOLOGY = 0,
  BALL_TOPOLOGY = 1,
  LINE_TOPOLOGY = 2,
  NUM_TOPOLOGIES = 3
} TopologyType;

class Topology {

public:
  TopologyType type;
  int parameter;

  Topology();
  Topology(TopologyType t, int p);
  Topology(const Topology &t);
  ~Topology();

  static std::string typeShortName[];
  static std::string typeFullName[];
  static std::string parameterName[];
  static TopologyType getType(std::string t);
};

#endif
