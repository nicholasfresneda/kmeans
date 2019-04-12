#include <vector>
using namespace std;


class Cluster {
    public:
    int xVal;
    int yVal;
    Cluster(int xVal, int yVal);

};

class Coord {
private:
    int xVal;
    int yVal;
    int nearestCluster;
    int getEuclideanDistance(Cluster cluster);

public:
    Coord(int xVal, int yVal, int cluster);
    int getCluster();
    void updateCentroid(vector<Cluster> newClusters);
};