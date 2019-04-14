#include "Cluster.hpp"
#include <math.h>
#include <fstream>
#include <string>
using namespace std;

Coord::Coord(int xVal, int yVal)
{
    this->x = xVal;
    this->y = yVal;
}

int Coord::getEuclideanDistance(Coord coord)
{
    double p1 = pow(this->x - coord.x, 2);
    double p2 = pow(this->y - coord.y, 2);
    return (int) sqrt(p1 + p2);
}

int Coord::getX()
{
    return x;
}

int Coord::getY()
{
    return y;
}

Cluster::Cluster(vector<pair<Coord, int>> coordPairs, vector<Coord> kClusters) : colorMap()
{
    this->coordPairs = coordPairs;
    this->kClusters = kClusters;
    converged = false;
    colorMap.insert(make_pair(-1, "black"));
    colorMap.insert(make_pair(0, "red"));
    colorMap.insert(make_pair(1, "blue"));
    colorMap.insert(make_pair(2, "green"));
    colorMap.insert(make_pair(3, "brown"));
    colorMap.insert(make_pair(4, "yellow"));
    colorMap.insert(make_pair(5, "purple"));
}

Cluster::~Cluster()
{
}

void Cluster::updateClusters()
{
    updateCoordMap();
    updateClusterCoords();
}

void Cluster::writeToDatafile(int fileNum)
{
    //iterate through map
    //writing each coordinates x and y and then cluster num to file
    ofstream myfile;
    std::string file("data" + to_string(fileNum) + ".dat" );

    myfile.open (file);
    for(unsigned int i = 0; i < coordPairs.size(); i++)
    {
        myfile << coordPairs.at(i).first.getX() << "\t" << coordPairs.at(i).first.getY() << "\t"
         << coordPairs.at(i).second << "\n";
    }

    myfile.close();
    std::string kfile("data" + to_string(fileNum) + "a.dat");
    myfile.open(kfile);
    for (unsigned int i = 0; i < kClusters.size(); i++)
    {
        //output each cluster with -1 as third number, to tell gnuplot to color the points the same
        myfile << kClusters.at(i).getX() << "\t" << kClusters.at(i).getY() << "\t" << i << "\n";
    }

    myfile.close();

    
}

void Cluster::updateCoordMap()
{
    //iterate through map
    //calculate closest cluster for each coordinate and update k num in map
    for(unsigned int i = 0; i < coordPairs.size(); i++)
    {
        Coord coord = coordPairs.at(i).first;
        int minDist = coord.getEuclideanDistance(kClusters.at(0));
        int count = 0;
        int index = 0;
        for(Coord cluster : kClusters)
        {
            int newDist = coord.getEuclideanDistance(cluster);
            if(newDist < minDist)
            {
                minDist = newDist;
                index = count;
            }
            
            count++;
        }

        coordPairs.at(i).second = index;
    }

}

void Cluster::updateClusterCoords()
{
    //iterate through k cluster vec
    //update cluster with average of each point in maps 
    
    //copy cluster to compare for later
    vector<Coord> copyCluster = kClusters;
    for (unsigned int i = 0; i < kClusters.size(); i++)
    {
        int sumX = 0;
        int sumY = 0;
        for (unsigned int j = 0; j < coordPairs.size(); j++)
        {
            if ((unsigned int) coordPairs.at(j).second == i)
            {
                sumX += coordPairs.at(j).first.getX();
                sumY += coordPairs.at(j).first.getY();
            }
            
        }

        Coord newCoord(sumX / coordPairs.size(), sumY / coordPairs.size());
        kClusters[i] = newCoord;
    }
    
    bool converged = true;
    for (unsigned int i = 0; i < kClusters.size(); i++)
    {
        if (copyCluster.at(i).getX() != kClusters.at(i).getX()
         && copyCluster.at(i).getY() != kClusters.at(i).getY())
        {
            converged = false;
            break;
        }
    }

    this->converged = converged;
}

