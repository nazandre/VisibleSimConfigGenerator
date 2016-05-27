#ifndef ROBOT_H_
#define ROBOT_H_

#include <string>
#include "vector3D.hpp"

typedef enum RobotType_t {
  UNKNOWN_ROBOT = -1,
  BLINKYBLOCKS_ROBOT = 0,
  SMART_BLOCKS_ROBOT = 1,
  CATOMS2D_ROBOT = 2,
  CATOMS3D_ROBOT = 3,
  NUM_ROBOTS = 4
} RobotType;

class Robot {

public:
  RobotType type;
  
  Robot();
  Robot(RobotType t);
  Robot(const Robot &r);
  ~Robot();
  
  static std::string typeShortName[];
  static std::string typeFullName[];
  static Vector3D typeVSFormatSize[];
  static Vector3D typeCompFormatSize[];
  static Vector3D defaultColor[];
  
  static RobotType getType(std::string t);
};

#endif
