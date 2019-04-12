#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Cluster.hpp"

using namespace std;

#define COL_SZ 2
#define REQ_ARGS 4

static int K_SZ;
static int ITER;
static int NUM_PTS;


void processInputs(int argc, char* argv[])
{
    if(argc != REQ_ARGS)
    {
        cout<<"Wrong inputs:\t\n"
        << "Usage: ./" << argv[0] << "<number of k clusters> <number of points> <iterations>\n";
        exit(1);
    }

    K_SZ = atoi(argv[1]);
    NUM_PTS = atoi(argv[2]);
    ITER = atoi(argv[3]);
}

int main(int argc, char* argv[])
{
    //initialize inputs
    processInputs(argc, argv);

    //initialize k clusters
    srand(time(NULL));
    unordered_map<Coord, int> *clusterInit = new unordered_map<Coord,int>();
    vector<Coord> kClusters;
    for(int i = 0; i < K_SZ; i++)
    {
        Coord newCoord(rand() % 100, rand() % 100);
        kClusters.push_back(newCluster);
    }

    //initialize coordinates and write to data file
    ofstream myfile;
    myfile.open ("data0.dat");
    for (int i = 0; i < NUM_PTS; i++)
    {
        int xVal = rand() % 100;
        int yVal = rand() % 100;

        //initialize all coordinates with random cluster (will be set later)
        Coord newCoord(xVal, yVal);
        //clusterInit kClusters[rand() % K_SZ]
        myfile << xVal << "\t" << yVal <<endl;
    }

    Cluster cluster(clusterInit, kClusters);
    myfile.close();

    //main loop 
    for (int i = 0; i < ITER; i++)
    {
        cluster.updateClusters(inputData, kClusters);
        cluster.writeToDatafile(i);    
    }

    delete[] inputData;
}