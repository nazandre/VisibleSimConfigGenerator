#ifndef COLOR_H_
#define COLOR_H_

#include "vector3D.hpp"

#define AQUA_COLOR Vector3D(18, 189, 185)
#define BLUE_COLOR Vector3D(0,0,255)
#define GRAY_COLOR Vector3D(100,100,100)
#define GREEN_COLOR Vector3D(0,255,0)
#define INDIGO_COLOR Vector3D(75, 0, 130)
#define ORANGE_COLOR Vector3D(255,140,0)
#define PURPLE_COLOR Vector3D(139, 0, 255)
#define RED_COLOR Vector3D(255,0,0)
#define YELLOW_COLOR Vector3D(255,255,0)

typedef enum color_t {
  RED = 0,
  ORANGE = 1,
  YELLOW = 2,
  GREEN = 3,
  AQUA = 4,
  BLUE = 5,
  INDIGO = 6,
  PURPLE = 7,
  GRAY = 8,
  NUM_COLORS
} color;

class Color {
private:
  static Vector3D colors[];
public:  
  static Vector3D& getColor(color i);
  static Vector3D& getRandom();
};

#endif
