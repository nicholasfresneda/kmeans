#include <vector>
#include <hashmap>

using namespace std;


class Coord 
{
private:
    int x;
    int y;
    int getEuclideanDistance(Coord coord);

public:
    Coord(int xVal, int yVal);
    int getX();
    int getY()
};

class Cluster 
{
private:
    unordered_map<Coord, int> *clusterMap;
    std::vector<Coord> kClusters;
    void updateCoordMap();
    void updateClusterCoords();
    
public:
    Cluster(unordered_map<Coord, int> *clusterMap, vector<Coord> kClusters);
    void updateClusters();
    void writeToDatafile(int fileNum);
    ~Cluster();


};

