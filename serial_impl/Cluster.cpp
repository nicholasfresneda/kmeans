#include "Coord.hpp"
#include <math.h>
using namespace std;

Coord::Coord(int xVal, int yVal)
{
    this->xVal = xVal;
    this->yVal = yVal;
}

int Coord::getEuclideanDistance(Cluster cluster)
{
    double p1 = pow(this->xVal - cluster.xVal, 2);
    double p2 = pow(this->yVal - cluster.yVal, 2);
    return (int) sqrt(p1 + p2);
}


Cluster::Cluster(unordered_map<Coord, int> *clusterMap, vector<Coord> kClusters)
{
    this->clusterMap = clusterMap;
    this->kClusters = kClusters;
}

Cluster::~Cluster()
{
    delete clusterMap;
}

Cluster::updateClusters()
{
    updateCoordMap();
    updateClusterCoords();
}

Cluster::writeToDatafile()
{
    //iterate through map
    //writing each coordinates x and y and then cluster num to file
}

Cluster::updateCoordMap()
{
    //iterate through map
    //calculate closest cluster for each coordinate and update k num in map

}

Cluster::updateClusterCoords()
{
    //iterate through k cluster vec
    //update cluster with average of each point in map
}

