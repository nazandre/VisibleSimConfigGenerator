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
  cerr << "Output: " << arguments.output << endl;
  cerr << "Color: " << boolalpha << arguments.colored << noboolalpha << endl;
  
  // Create Configuration
  Robot robot(Robot::getType(arguments.robot));
  int parameter = stoi(arguments.parameter);
  double occupancyRatio = stof(arguments.occupancyRatio);
  Topology topology(Topology::getType(arguments.topology),parameter);
  LatticeType latticeType = Robot::getLatticeType(robot.type);
  Vector3D size;

  if (arguments.size == "" ) {
    size = topology.getLatticeSize(latticeType,occupancyRatio);
    cerr << "Occupancy ratio: " << occupancyRatio << endl;
  } else {
    size = Vector3D(arguments.size);
    topology.checkSize(latticeType,size);
  }
  cerr << "Lattice size: " << size << endl;
  
  Configuration configuration(robot,size,arguments.colored);

  // Generate configuration topology
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
