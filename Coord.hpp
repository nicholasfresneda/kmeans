#include <vector>
using namespace std;


class Cluster {
    int xVal;
    int yVal;
    Cluster(int xVal, int yVal);

};

class Coord {

private:
    int xVal;
    int yVal;
    int cluster;

public:
    Coord(int xVal, int yVal, int cluster);
    int getCluster();
    void updateCluster(vector<Cluster> newClusters);
};