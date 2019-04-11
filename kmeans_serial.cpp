#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "Coord.hpp"

using namespace std;
#define ROW_SZ 100
#define COL_SZ 2
#define K_SZ 3

int main()
{
    srand(time(NULL));
    int** input_data = new int*[ROW_SZ];
    int k[K_SZ];

    for(int i = 0; i < k[K_SZ]; i++)
    {
        k[i] = rand();
    }
    for (int i = 0; i < ROW_SZ; i++)
    {
        input_data[i] = new int[COL_SZ];
    }
    ofstream myfile;
    myfile.open ("example.txt");
    
    for (int i = 0; i < ROW_SZ; i++)
    {
        int xVal = rand() % 100;
        int yVal = rand() % 100;
        myfile << xVal << "\t" << yVal <<endl;
        input_data[i][0] = xVal;
        input_data[i][1] = yVal;
    }
    myfile.close();

    delete[] input_data;
}