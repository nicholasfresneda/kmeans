#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <unordered_map>
#include <string>
using namespace std;


class Coord {
private:
    int x;
    int y;

public:
    Coord(int xVal, int yVal);
    int getX();
    int getY();
    int getEuclideanDistance(Coord coord);

};

class Cluster {
private:
    vector<pair<Coord, int>> coordPairs;
    std::vector<Coord> kClusters;
    void updateCoordMap();
    void updateClusterCoords();
    unordered_map<int, string> colorMap;
    
public:
    Cluster(vector<pair<Coord, int>> clusterInit, vector<Coord> kClusters);
    void updateClusters();
    void writeToDatafile(int fileNum);
    ~Cluster();


};

#endif

