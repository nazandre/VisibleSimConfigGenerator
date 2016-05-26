#include <iostream>
#include <cstdlib>
#include "arguments.hpp"

#include "robot.hpp"
#include "topology.hpp"

using namespace std;

Arguments::Arguments() {}

Arguments::Arguments(int argc, char *argv[]) {

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
      topology = argv[1];
      argc--;
      argv++;
      parameter = argv[1];
      argc--;
      argv++;
      break;
    case 'r':
      robot = argv[1];
      argc--;
      argv++;
      break;
    case 's':
      size = argv[1];
      argc--;
      argv++;
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
  RobotType robotType = Robot::getType(robot);
  if (robotType == UNKNOWN_ROBOT) {
    cerr << "ERROR: Unknown robot type " << robot << endl;
    help();
  }
  
  if(topology == "") {
    cerr << "ERROR: No topology specified" << endl;
    help();
  }
  TopologyType topologyType = Topology::getType(topology);
  if (topologyType == UNKNOWN_TOPOLOGY) {
    cerr << "ERROR: Unknown topology type " << robot << endl;
    help();
  }

  if (output == "") {
    cerr << "WARNING: No ouput file specified."
	 << "Will export the configuration in ? "
	 << endl;
  }

  if (size == "") {
    cerr << "WARNING: No lattice size specified."
	 << "Will use automatically computed values."
	 << endl;
  }
  
  /*
  if (input == "") {
    cerr << "ERROR: No input file" << endl;
    help();
  }

  size_t lastDot = input.find_last_of(".");
  string ext = input.substr(lastDot + 1);
  if (ext != "xml") {
    help();
  }

  if(target == "") {
    cerr << "ERROR: No target lattice specified" << endl;
    help();
  }

  LatticeType t = Lattice::getType(target);

  if (t == UNKNOWN_LATTICE) {
    cerr << "ERROR: Unknown target lattice " << target << endl;
    help();
  }
  
  if (output == "") {
    size_t lastSlash = input.find_last_of("/\\");
    string n =  input.substr(0, lastDot).substr(lastSlash+1);
    output = n + ".aj";
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
  size = a.size;
}

Arguments::~Arguments() { }

void Arguments::help() {
  cerr << "Usage: VisibleSimConfigGenerator -r <target robot system> -s <lattice size (2D or 3D)> -o <ouput xml file> -t <topology to generate> <topology parameter> [options]"<< endl;

  cerr << "Supported target robot systems(<target robot system>): " << endl;
  for (int i = 0; i < NUM_ROBOTS; i++) {
    cerr << "  " << Robot::typeShortName[i]
	 << ": " << Robot::typeFullName[i] << endl;
  }

  cerr << "Lattice size format:" << endl;
  cerr << "  \"x,y\" for 2D configurations" << endl;
  cerr << "  \"x,y,z\" for 3D configurations" << endl;
  
  cerr << "Supported topology (<topology to generate>): " << endl;
  for (int i = 0; i < NUM_TOPOLOGIES; i++) {
    cerr << "  " << Topology::typeShortName[i]
	 << ": " << Topology::typeFullName[i]
	 << " (parameter: " << Topology::parameterName[i] << ")"<< endl;
  }

  
  
  cerr <<"Options:" << endl;
  //cerr <<"-o <output aj file> : output file for GraphAnalyzer" << endl;
  cerr <<"-h: print this usage and exit" << endl;

  exit(EXIT_SUCCESS);
} 
