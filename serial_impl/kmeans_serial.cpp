#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Cluster.hpp"
#include <unordered_map>

using namespace std;

#define COL_SZ 2
#define REQ_ARGS 4
#define MAX_K 6
#define MAX_PT 800
static int K_SZ;
static int ITER;
static int NUM_PTS;


void processInputs(int argc, char* argv[])
{
    if(argc != REQ_ARGS)
    {
        cout<<"Wrong inputs:\t\n"
        << "Usage: " << argv[0] << " <number of k clusters> <number of points> <iterations>\n";
        exit(1);
    }

    K_SZ = atoi(argv[1]);
    if (K_SZ > MAX_K)
    {
        cout<<"Error: Only 6 or fewer k clusters supported\n";
    }

    NUM_PTS = atoi(argv[2]);
    ITER = atoi(argv[3]);
}

int main(int argc, char* argv[])
{
    //initialize inputs
    processInputs(argc, argv);

    //initialize k clusters
    srand(time(NULL));
    vector<pair<Coord, int>> clusterInit;
    vector<Coord> kClusters;
    for(int i = 0; i < K_SZ; i++)
    {
        Coord newCoord(rand() % MAX_PT, rand() % MAX_PT);
        kClusters.push_back(newCoord);
    }

    //initialize coordinates and write to data file
    for (int i = 0; i < NUM_PTS; i++)
    {
        int xVal = rand() % MAX_PT;
        int yVal = rand() % MAX_PT;

        //initialize all coordinates with zero as cluster (will be set later)
        Coord newCoord(xVal, yVal);
        // pair<Coord, int> newMapVal(newCoord, 0);
        clusterInit.push_back(std::make_pair(newCoord, 0));
    }

    Cluster cluster(clusterInit, kClusters);

    //main loop 
    for (int i = 0; i < ITER; i++)
    {
        cluster.updateClusters();
        cluster.writeToDatafile(i);    
        if (cluster.converged)
        {
            break;
        }
    }

}