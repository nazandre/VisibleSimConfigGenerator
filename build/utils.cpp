#include <cstdlib>
#include <iostream>
#include "utils.hpp"

using namespace std;

void Utils::swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void Utils::notImplementedYet(string s) {
  cerr << "ERROR: This functionality has not been implemented yet... " << s << endl;
  exit(EXIT_FAILURE);
}
