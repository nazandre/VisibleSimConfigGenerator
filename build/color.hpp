#ifndef COLOR_H_
#define COLOR_H_

#include "vector3D.hpp"

#define BLUE_COLOR Vector3D(0,0,255)
#define GRAY_COLOR Vector3D(100,100,100)
#define GREEN_COLOR Vector3D(0,255,0)
#define ORANGE_COLOR Vector3D(255,140,0)
#define RED_COLOR Vector3D(255,0,0)
#define YELLOW_COLOR Vector3D(255,255,0)

typedef enum color_t {
  RED = 0,
  ORANGE = 1,
  YELLOW = 2,
  GREEN = 3,
  BLUE = 4,
  GRAY = 5,
  NUM_COLORS = 6
} color;

class Color {
private:
  static Vector3D colors[];
public:
  
  static Vector3D& getColor(color i);
};

#endif
