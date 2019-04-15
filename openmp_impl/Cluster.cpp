#include "Cluster.hpp"
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include <omp.h>

using namespace std;

Coord::Coord(int xVal, int yVal)
{
    this->x = xVal;
    this->y = yVal;
}

int Coord::getEuclideanDistance(Coord coord)
{
    double p1 = pow(coord.x - this->x, 2);
    double p2 = pow(coord.y - this->y, 2);
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

void Coord::setX(int x)
{
    this->x = x;
}

void Coord::setY(int y)
{
    this->y = y;
}

Cluster::Cluster(vector<pair<Coord, int>> coordPairs, vector<Coord> kClusters)
{
    this->coordPairs = coordPairs;
    this->kClusters = kClusters;
    converged = false;
}

Cluster::~Cluster()
{
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
        myfile << kClusters.at(i).getX() << "\t" << kClusters.at(i).getY() << "\t" << -1 << "\n";
    }

    myfile.close();
}

void Cluster::updateCoordMap()
{
    //iterate through map
    //calculate closest cluster for each coordinate and update k num in map
    #pragma omp parallel for 
    for(unsigned int i = 0; i < coordPairs.size(); i++)
    {
        Coord coord = coordPairs[i].first;
        int minDist = coord.getEuclideanDistance(kClusters.at(0));
        int count = 0;
        int index = 0;
        vector<int> distances();
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

        coordPairs[i].second = index;
    }

}

void Cluster::updateClusterCoords()
{
    //iterate through k cluster vec
    //update cluster with average of each point in maps 
    
    //copy cluster to compare for later
    vector<Coord> copyCluster = kClusters;
    #pragma omp parallel for
    for (unsigned int i = 0; i < kClusters.size(); i++)
    {
        int sumX = 0;
        int sumY = 0;
        int count = 0;
        for (unsigned int j = 0; j < coordPairs.size(); j++)
        {
            if ((unsigned int) coordPairs[j].second == i)
            {
                count++;
                sumX += coordPairs[j].first.getX();
                sumY += coordPairs[j].first.getY();
            }
        }

        Coord newCoord(0,0);
        if (count != 0)
        {
           newCoord.setX(sumX / count);
           newCoord.setY(sumY / count);
        }

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

