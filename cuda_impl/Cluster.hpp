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
public:
    Cluster(int kSize, long coordSize);
    void updateCoordMap();
    void updateClusterCoords();
    void writeToDatafile(int fileNum);
    bool converged;
    ~Cluster();


};

#endif

