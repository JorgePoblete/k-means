SRC_FOLDER=./src/
SRC_FILES=kmeans.cpp utils.cpp main.cpp
SRC=$(addprefix $(SRC_FOLDER),$(SRC_FILES))
OBJ=$(SRC:.cpp=.o)
EIGEN_PATH=/usr/local/include/eigen3/
INCLUDES=-I $(EIGEN_PATH)
CC=g++
CCFLAGS=-Wall -std=c++11 -O3 -ffast-math
EXEFLAGS=-xHost
OBJFLAGS=-c
LDLIBS=-fopenmp
EXE=kmeans

$(VERBOSE).SILENT:

all: clean $(SRC) $(EXE)
	rm -f $(SRC_FOLDER)*.o

.cpp.o:
	$(CC) $(OBJFLAGS) $(CCFLAGS) $(LDLIBS) $(INCLUDES) $< -o $@

$(EXE): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LDLIBS) $(INCLUDES) $(EXEFLAGS) -o $(EXE)

clean:
	rm -f $(SRC_FOLDER)*.o $(EXE)
