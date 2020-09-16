/*
#include <bits/stdc++.h>
#include <vector>  
#include <iostream>
#include <fstream>
*/
#include <fstream>
#include <string> 
#include <cstdlib>
#include "oneDwave.hpp"
#include <iostream>

using namespace std; 


void oneDwave::initialise_mesh(){
    int N = Ntot - 2;
    float zero = 0;
    float u = 100;

    for (int i=0; i<N; i++)
    {
        if ((dx*i < 40)||(dx*i > 60))
        {
            mesh[0][i+1] = zero;
            //*(*(mesh)+i+1) = zero;
        }
        else 
        {
            //mesh[0][i+1] = 100;
            *(*(mesh)+i+1) = u;
        }
    }
    std::cout << "Mesh initialised" << std::endl;
}
    
void oneDwave::fix_mesh_edge(int row){
*(*(mesh+row)+0) = *(*(mesh+row) + Ntot -2);
*(*(mesh+row) + Ntot -1) = *(*(mesh+row) + 1);
}

void oneDwave::Write_Array_2_File(string method, float time, int row){
    string title = "./data/t" + std::to_string(time) + "_c" + std::to_string(CFL) + "_" + method + ".dat";
    ofstream myfile;
    myfile.open(title);
    myfile << "# X              u " << endl << "#-------------------------------------" << endl ;
    
    float x;
    float u;
    for(int i = 0; i < (Ntot-2); i++){
        x = dx * i;
        u = mesh[row][i+1];
        myfile << x << ' ' << u << endl;
    }
    myfile.close();
}
oneDwave::oneDwave(){}
oneDwave::oneDwave(float Length, int NumberOfKnots, float CFL_user, float velocity):oneDwave::oneDwave()
{
    Ntot = NumberOfKnots;
    dx = Length / (Ntot - 3);
    CFL = CFL_user;
    dt = CFL * dx / velocity;   	
    
    mesh = new float*[2]; // dynamic array (size 10) of pointers to int
    for (int i = 0; i < 2; ++i) 
    {
        mesh[i] = new float[Ntot];
    // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
    }
}


void BackSolver::solve(float SimTime){
    this->initialise_mesh();

    int CurrentIndex = 0;
    int LastIndex = 1;
    float CurrentTime = 0;

    std::cout << "Start solve back" << std::endl;

    while (CurrentTime < SimTime)
    {

        LastIndex = CurrentIndex;
        CurrentIndex = abs(CurrentIndex-1);
    
        this->fix_mesh_edge(LastIndex);

        CurrentTime = CurrentTime + dt;

        for ( int i = 1; i <= Ntot-2; i++)
        {
            mesh[CurrentIndex][i] = mesh[LastIndex][i] - CFL*(mesh[LastIndex][i]-mesh[LastIndex][i-1]);
        }    
        this->Write_Array_2_File("back", CurrentTime, CurrentIndex);
    }      

    std::cout << "End solve back" << std::endl;  
}


void FrontSolver::solve(float SimTime){
    this->initialise_mesh();

    int CurrentIndex = 0;
    int LastIndex = 1;
    float CurrentTime = 0;

    std::cout << "Start solve front" << std::endl;

    while (CurrentTime < SimTime)
    {

        LastIndex = CurrentIndex;
        CurrentIndex = abs(CurrentIndex-1);
    
        this->fix_mesh_edge(LastIndex);

        CurrentTime = CurrentTime + dt;

        for ( int i = 1; i <= Ntot-2; i++)
        {
            mesh[CurrentIndex][i] = mesh[LastIndex][i] - CFL*(mesh[LastIndex][i+1]-mesh[LastIndex][i]);
        }    
        this->Write_Array_2_File("front", CurrentTime, CurrentIndex);
    }      

    std::cout << "End solve front" << std::endl;  
}

void MidSolver::solve(float SimTime){
    this->initialise_mesh();

    int CurrentIndex = 0;
    int LastIndex = 1;
    float CurrentTime = 0;

    std::cout << "Start solve mid" << std::endl;

    while (CurrentTime < SimTime)
    {

        LastIndex = CurrentIndex;
        CurrentIndex = abs(CurrentIndex-1);
    
        this->fix_mesh_edge(LastIndex);

        CurrentTime = CurrentTime + dt;

        for ( int i = 1; i <= Ntot-2; i++)
        {
            mesh[CurrentIndex][i] = mesh[LastIndex][i] - CFL*(mesh[LastIndex][i+1]-mesh[LastIndex][i-1])/2;
        }    
        this->Write_Array_2_File("mid", CurrentTime, CurrentIndex);
    }      

    std::cout << "End solve mid" << std::endl;  
}



