#include "Cluster.hpp"
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>

#define MAX_PT 800
using namespace std;


__global__ void updateCoordKernel(long coordSize, int* coordXVals, int* coordYVals, 
                                int* clusterXVals, int* clusterYVals, int kSize,
                                int* coordKMaps)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = tid; i < coordSize; i+= stride)
    {
        int coordX = coordXVals[i];
        int coordY = coordYVals[i];

        //set to first cluster's distance, will be updated in loop
        double p1 = (coordX - clusterXVals[0]) * (coordX - clusterXVals[0]);
        double p2 = (coordY - clusterYVals[0]) * (coordY - clusterYVals[0]);
        int minDist = (int) sqrt(p1 + p2);
        int index = 0;
        for (int j = 1; j < kSize; j++)
        {
            double p1 = (coordX - clusterXVals[j]) * (coordX - clusterXVals[j]);
            double p2 = (coordY - clusterYVals[j]) * (coordY - clusterYVals[j]);
            int newDist = (int) sqrt(p1 + p2);
            if (newDist < minDist)
            {
                minDist = newDist;
                index = j;
            }
        }

        coordKMaps[i] = index;
    }
    
}

Cluster::Cluster(int kSize, long coordSize)
{
    this->kSize = kSize;
    this->coordSize = coordSize;
    //allocate and initialize member variables
    coordXVals = new int(coordSize);
    coordYVals = new int(coordSize);
    coordKMaps = new int(coordSize);
    clusterXVals = new int(kSize);
    clusterYVals = new int(kSize);
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
    for(unsigned int i = 0; i < coordSize; i++)
    {
        myfile << coordXVals[i] << "\t" << coordYVals[i] << "\t"
         << coordKMaps[i] << "\n";
    }

    myfile.close();
    std::string kfile("data" + to_string(fileNum) + "a.dat");
    myfile.open(kfile);
    for (unsigned int i = 0; i < kSize; i++)
    {
        //output each cluster with -1 as third number, to tell gnuplot to color the points the same
        myfile << clusterXVals[i] << "\t" << clusterYVals[i] << "\t" << -1 << "\n";
    }

    myfile.close();
}

void Cluster::updateCoordMap()
{
    //iterate through map
    //calculate closest cluster for each coordinate and update k num in map
    
    
    static bool firstTime = 1;

    if (firstTime)
    {
        cudaMallocManaged(&coordXVals, sizeof(int) * coordSize);
        cudaMallocManaged(&coordYVals, sizeof(int) * coordSize);
        cudaMallocManaged(&coordKMaps, sizeof(int) * coordSize);
        cudaMallocManaged(&clusterXVals, sizeof(int) * kSize);
        cudaMallocManaged(&clusterYVals, sizeof(int) * kSize);
        firstTime = 0;
        srand(time(NULL));
        for (int i = 0; i < coordSize; i++)
        {
            coordXVals[i] = rand() % MAX_PT;
            coordYVals[i] = rand() % MAX_PT;
            
            //set k cluster for each coord to 0, will be changed later
            coordKMaps[i] = 0;
        }

        for(int i = 0; i < kSize; i++)
        {
            clusterXVals[i] = rand() % MAX_PT;
            clusterYVals[i] = rand() % MAX_PT;
        }
    }
    

    int blockSize = 256;
    int numBlocks = (coordSize + blockSize - 1) / blockSize;
    updateCoordKernel<<<numBlocks, blockSize>>>(coordSize, coordXVals, coordYVals,
                                            clusterXVals, clusterYVals, kSize, coordKMaps);

    cudaDeviceSynchronize();
}

void Cluster::updateClusterCoords()
{
    //iterate through k cluster vec
    //update cluster with average of each point in maps 
    
    //copy cluster to compare for later
    int copyXCluster[kSize];
    int copyYCluster[kSize];
    for (int i = 0; i < kSize; i++)
    {
        copyXCluster[i] = clusterXVals[i];
        copyYCluster[i] = clusterYVals[i];
    }
    for (unsigned int i = 0; i < kSize; i++)
    {
        int sumX = 0;
        int sumY = 0;
        int count = 0;
        for (unsigned int j = 0; j < coordSize; j++)
        {
            if ((unsigned int) coordKMaps[j] == i)
            {
                count++;
                sumX += coordXVals[j];
                sumY += coordYVals[j];
            }
        }

        int newXVal = 0;
        int newYVal = 0;
        if (count != 0)
        {
           newXVal = sumX / count;
           newYVal = sumY / count;
        }

        clusterXVals[i] = newXVal;
        clusterYVals[i] = newYVal;
    }
    
    bool converged = true;
    for (unsigned int i = 0; i < kSize; i++)
    {
        if (copyXCluster[i] != clusterXVals[i]
         || copyYCluster[i] != clusterYVals[i])
        {
            converged = false;
            break;
        }
    }

    this->converged = converged;
}

