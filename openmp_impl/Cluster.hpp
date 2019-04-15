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
    void setX(int x);
    void setY(int y);
    int getEuclideanDistance(Coord coord);

};

class Cluster {
private:
    vector<pair<Coord, int>> coordPairs;
    std::vector<Coord> kClusters;
    
public:
    Cluster(vector<pair<Coord, int>> clusterInit, vector<Coord> kClusters);
    void updateCoordMap();
    void updateClusterCoords();
    void writeToDatafile(int fileNum);
    bool converged;
    ~Cluster();


};

#endif

