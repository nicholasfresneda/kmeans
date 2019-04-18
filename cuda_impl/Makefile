CC=g++
NVCC = nvcc
CFLAGS=-O3 -std=c++11 
LDFLAGS= 
SOURCES=kmeans_cuda.cpp Cluster.cu
OBJECTS=kmeans_cuda.o Cluster.o
EXECUTABLE=kmeans_cuda

all: $(SOURCES) $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(NVCC) $(LDFLAGS) $(CFLAGS) $(OBJECTS) -o $@

kmeans_cuda.o: kmeans_cuda.cpp
	$(NVCC) $(LDFLAGS) $(CFLAGS) -c $< -o $@

Cluster.o: Cluster.cu
	$(NVCC) $(LDFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: clean

clean:
	rm -rf *.o *.png kmeans_cuda *.dat

