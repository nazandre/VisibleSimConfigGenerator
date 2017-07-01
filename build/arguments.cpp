#include <iostream>
#include <cstdlib>
#include "arguments.hpp"

#include "robot.hpp"
#include "topology.hpp"

#define DEFAULT_OCCUPANCY_RATIO "0.5"

using namespace std;

Arguments::Arguments() {}

Arguments::Arguments(int argc, char *argv[]) {
  TopologyType topologyType = UNKNOWN_TOPOLOGY;
  RobotType robotType = UNKNOWN_ROBOT;

  occupancyRatio = "-1";
  
  colored = false;
  
  argv++;
  argc--;

  while ((argc > 0) && (argv[0][0] == '-')) {
    switch(argv[0][1]) {
    case 'o':
      readOne(output,argc,&argv);
      //output = argv[1];
      //argc--;
      //argv++;
      break;
    case 't':
      readOne(topology,argc,&argv);
      readOne(parameter,argc,&argv);      
      break;
    case 'r':
      readOne(robot,argc,&argv);
      break;
    case 's':
      readOne(size,argc,&argv);
      break;
    case 'd':
      readOne(occupancyRatio,argc,&argv);
      break;
    case 'c':
      colored = true;
      break;
    case 'h':
      help();
      break;
    default:
      cerr << "ERROR: Unknown argument -" <<  argv[0][1] << endl;
      help();
    }
    argc--;
    argv++;
  }

  if(robot == "") {
    cerr << "ERROR: No target robot specified" << endl;
    help();
  }
  
  robotType = Robot::getType(robot);

  if (robotType == UNKNOWN_ROBOT) {
    cerr << "ERROR: Unknown robot type " << robot << endl;
    help();
  }
  
  if(topology == "") {
    cerr << "ERROR: No topology specified" << endl;
    help();
  }
  topologyType = Topology::getType(topology);
 
  if (topologyType == UNKNOWN_TOPOLOGY) {
    cerr << "ERROR: Unknown topology type " << topology << endl;
    help();
  }

  if (output == "") {
    cerr << "ERROR: No ouput file specified." << endl;
    help();
  }

  if (size == "" &&
      topologyType == RANDOM_TOPOLOGY &&
      occupancyRatio == "-1") {
    occupancyRatio = DEFAULT_OCCUPANCY_RATIO;
    cerr << "WARNING: no lattice size or occupancy ratio given. Will use default value." << endl;
  }
  
  /*if (size == "" &&
      topologyType == RANDOM_TOPOLOGY &&
      (occupancyRatio < 0 || occupancyRatio > 1)) {
    cerr << "ERROR: No lattice size specified." << endl;
    help();
    }*/
}

void Arguments::readOne(string &s, int &argc, char **argv[]) {
  s = (*argv)[1];
  argc--;
  (*argv)++;
}

Arguments::Arguments(const Arguments &a) {
  output = a.output;
  robot = a.robot;
  topology = a.topology;
  parameter = a.parameter;
  occupancyRatio = a.occupancyRatio;
  size = a.size;
  colored = a.colored;
}

Arguments::~Arguments() { }

void Arguments::help() {
  cerr << "Usage: VisibleSimConfigGenerator -r <target robot system> -o <ouput xml file> -t <topology to generate> <topology parameters> [options]"<< endl;

  cerr << "Supported target robot systems(<target robot system>): " << endl;
  for (int i = 0; i < NUM_ROBOTS; i++) {
    cerr << "  " << Robot::typeShortName[i]
	 << ": " << Robot::typeFullName[i] << endl;
  }
  
  cerr << "Supported topologies (<topology to generate>): " << endl;
  for (int i = 0; i < NUM_TOPOLOGIES; i++) {
    cerr << "  " << Topology::typeShortName[i]
	 << ": " << Topology::typeFullName[i]
	 << " (parameter: " << Topology::parameterName[i] << ")"<< endl;
  }

  cerr <<"Options:" << endl;
  cerr << "  -c: enable color" << endl;
  cerr << "  -h: print this usage and exit" << endl;
  cerr << "  -s \"x,y,z\": Lattice size 3D" << endl;
  cerr << "  -d \"d\": Occupancy ratio (#cells/#modules, 0 < d <= 1), only for random configurations." << endl;

  exit(EXIT_SUCCESS);
} 
