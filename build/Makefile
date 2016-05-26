CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = visibleSimConfigGenerator
INCLUDES =
LIBS = 
OBJ_FILES = arguments.o node.o utils.o generator.o vector3D.o configuration.o robot.o topology.o lattice.o visibleSimConfigGenerator.o

all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)
