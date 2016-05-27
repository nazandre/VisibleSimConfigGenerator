#include <iostream>

#include "vector3D.hpp"

using namespace std;

Vector3D::Vector3D() {};

Vector3D::Vector3D(int _x, int _y, int _z) {
  x = _x;
  y = _y;
  z = _z;
}

Vector3D::Vector3D(string &s, int v) {
  size_t coma1 = s.find_first_of(",");
  size_t coma2 = s.find_last_of(",");
  if (coma1 == coma2) {
    // 2D:
    x = stoi(s.substr(0,coma1));
    y = stoi(s.substr(coma1+1));
    z = v;
  } else {
    // 3D:
    x = stoi(s.substr(0,coma1));
    y = stoi(s.substr(coma1+1,coma2-coma1-1));
    z = stoi(s.substr(coma2+1));
  }
}

Vector3D::Vector3D(const Vector3D &v) {
  x = v.x;
  y = v.y;
  z = v.z;
}

Vector3D::~Vector3D() {}

string Vector3D::getString() const {
  return getString3D();
}

string Vector3D::getString2D() const {
  return to_string(x) + "," + to_string(y);
}

string Vector3D::getString3D() const {
  return to_string(x) + "," + to_string(y) + "," + to_string(z);
}

std::ostream& operator<<(std::ostream &os, const Vector3D &v) {
  os << "(" << v.getString() << ")";
  return os;
}

Vector3D operator+(const Vector3D  &v1, const Vector3D &v2) {
  return Vector3D(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
}

Vector3D operator*(const Vector3D  &v1, const Vector3D &v2) {
  return Vector3D(v1.x*v2.x,v1.y*v2.y,v1.z*v2.z);
}

Vector3D operator/(const Vector3D  &v1, const int &i) {
  return Vector3D(v1.x/i,v1.y/i,v1.z/2);
}
