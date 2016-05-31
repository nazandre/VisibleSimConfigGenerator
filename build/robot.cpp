#include "robot.hpp"
#include "color.hpp"

using namespace std;

#define BB_SIZE Vector3D(40,40,41)
#define SB_SIZE Vector3D(25,25,11)
#define C2_VS_FORMAT_SIZE Vector3D(1,5,1)
#define C2_COMP_FORMAT_SIZE Vector3D(1,1,1)
#define C3_SIZE Vector3D(10,10,10)

string Robot::typeShortName[] = {"bb", "sb", "c2", "c3"};
string Robot::typeFullName[] = {"blinkyblocks", "smartblocks", "catoms2d", "catoms3d"};
Vector3D Robot::typeVSFormatSize[] = {BB_SIZE, SB_SIZE, C2_VS_FORMAT_SIZE, C3_SIZE};
Vector3D Robot::typeCompFormatSize[] = {BB_SIZE, SB_SIZE, C2_COMP_FORMAT_SIZE, C3_SIZE};
Vector3D Robot::defaultColor[] = {GREEN_COLOR, GRAY_COLOR, GRAY_COLOR, GRAY_COLOR};

Robot::Robot() {}

Robot::Robot(RobotType t) {
  type = t;
}

Robot::Robot(const Robot &r) {
  type = r.type;
}

Robot::~Robot() {}
  
RobotType Robot::getType(std::string t) {
  for(int i = 0; i < NUM_ROBOTS; i++) {
    if(t == typeShortName[i] || t == typeFullName[i]) {
      return RobotType(i);
    }
  }
  return UNKNOWN_ROBOT;
}

Vector3D&  Robot::getTypeVSFormatSize() {
  return typeVSFormatSize[type];
}

Vector3D&  Robot::getTypeCompFormatSize() {
  return typeCompFormatSize[type];
}

Vector3D&  Robot::getDefaultColor() {
  return defaultColor[type];
}
