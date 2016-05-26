#include "robot.hpp"

using namespace std;

#define BB_SIZE Vector3D(40,40,41)
#define SB_SIZE Vector3D(25,25,11)
#define C2_SIZE Vector3D(1,5,1)
#define C3_SIZE Vector3D(10,10,10)

#define GREEN Vector3D(0,255,0)
#define GRAY Vector3D(100,100,100)

string Robot::typeShortName[] = {"bb", "sb", "c2", "c3"};
string Robot::typeFullName[] = {"blinkyblocks", "smartblocks", "catoms2d", "catoms3d"};
Vector3D Robot::typeSize[] = {BB_SIZE, SB_SIZE, C2_SIZE, C3_SIZE};
Vector3D Robot::defaultColor[] = {GREEN, GRAY, GRAY, GRAY};

Robot::Robot() {}

Robot::Robot(RobotType t) {
  type = t;
  size = typeSize[type];
}

Robot::Robot(const Robot &r) {
  type = r.type;
  size = r.size;
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
