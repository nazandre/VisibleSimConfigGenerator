#include <random>
#include "color.hpp"

using namespace std;

Vector3D Color::colors[] = {RED_COLOR, ORANGE_COLOR, YELLOW_COLOR,
			    GREEN_COLOR, AQUA_COLOR, BLUE_COLOR,
			    INDIGO_COLOR, PURPLE_COLOR, GRAY_COLOR};

Vector3D& Color::getColor(color i) {
  return colors[i%NUM_COLORS];
}

Vector3D& Color::getRandom() {
  random_device r;
  default_random_engine e1(r());
  uniform_int_distribution<int> uniform_dist1(0, NUM_COLORS-1);
  int cid = uniform_dist1(e1);
  return colors[cid];
}
