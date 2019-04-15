#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Cluster.hpp"
#include <unordered_map>
#include <ctime>

using namespace  std;

#define COL_SZ 2
#define REQ_ARGS 4
#define MAX_K 6
#define MAX_PT 800
static int K_SZ;
static int ITER;
static long NUM_PTS;


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

    Cluster cluster(K_SZ, NUM_PTS);
    //main loop 
    for (int i = 0; i < ITER; i++)
    {
        cluster.updateCoordMap();
        cluster.writeToDatafile(i);  
        cluster.updateClusterCoords();  
        if (cluster.converged)
        {
            break;
        }
    }

}