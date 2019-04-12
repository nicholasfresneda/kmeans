#include "Coord.hpp"
#include <math.h>
using namespace std;

Coord::Coord(int xVal, int yVal, int cluster)
{
    this->xVal = xVal;
    this->yVal = yVal;
    this->nearestCluster = cluster;
}

int Coord::getCluster()
{
    return nearestCluster;
}

void Coord::updateCentroid(vector<Cluster> clusters)
{
    vector<int> distances;
    for (Cluster cluster : clusters)
    {
        distances.push_back(getEuclideanDistance(cluster));
    }

    int min = distances.at(0);
    for (int distance : distances)
    {
        if(min > distance)
        {
            min = distance;
        }
    }

    this->nearestCentroid = min;
}

int Coord::getEuclideanDistance(Cluster cluster)
{
    double p1 = pow(this->xVal - cluster.xVal, 2);
    double p2 = pow(this->yVal - cluster.yVal, 2);
    return (int) sqrt(p1 + p2);
}

Cluster::Cluster(int x, int y)
{
    this->xVal = x;
    this->yVal = y;
}
