#include <cstdlib>
#include <iostream>
#include <fstream>

#include "arguments.hpp"
#include "configuration.hpp"
#include "topology.hpp"
#include "generator.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  Arguments arguments(argc,argv);
  cerr << "Target robot: " << arguments.robot << endl;
  cerr << "Topology: " << arguments.topology;
  cerr << ", parameter: " << arguments.parameter << endl;
  cerr << "Lattice size: " << arguments.size << endl;
  cerr << "Output: " << arguments.output << endl;

  // Create Configuration
  Vector3D size(arguments.size);
  Robot robot(Robot::getType(arguments.robot));
  Configuration configuration(robot,size);

  // Generate configuration topology
  int parameter = stoi(arguments.parameter);
  Topology topology(Topology::getType(arguments.topology),parameter);
  Generator generator(configuration,topology);
  generator.generate();
  
  cerr << "Configuration with " << configuration.getSize() << " modules generated!" << endl;

  // Export to VisibleSim
  ofstream output;
  output.open (arguments.output);
  configuration.exportToVisibleSim(output);
  
  cerr << "Configuration exported in " << arguments.output << endl;
  return EXIT_SUCCESS;
}
