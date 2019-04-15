CC=g++
CFLAGS=-O3 -std=c++11 -Wall
LDFLAGS= -lm -fopenmp
SOURCES=kmeans_omp.cpp Cluster.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=kmeans_omp

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf *.o *.png kmeans_serial *.dat

