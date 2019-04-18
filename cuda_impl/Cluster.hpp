#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

class Cluster {
private:
   // vector<pair<Coord, int>> coordPairs;
    int* coordXVals;
    int* coordYVals;
    int* coordKMaps;
    int* clusterXVals;
    int* clusterYVals;
    int kSize;
    long coordSize;
    int* d_coordXVals;
    int* d_coordYVals;
    int* d_coordKMaps;
    int* d_clusterXVals;
    int* d_clusterYVals;
public:
    Cluster(int kSize, long coordSize);
    void updateCoordMap();
    void updateClusterCoords();
    void writeToDatafile(int fileNum);
    bool converged;
    ~Cluster();


};

#endif

