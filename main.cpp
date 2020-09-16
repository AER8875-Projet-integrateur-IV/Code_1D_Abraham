// Your First C++ Program

#include <iostream>
//#include <fstream>
#include <stdlib.h>     /* atoi */
#include <unistd.h>
//#include <cstdlib>
//#include <string> 
#include "oneDwave.hpp"

int main(int argc, char** argv) {
    int opt;
    int N; 
    int Ntot;
    float CFL;
    float L = 100;          // m
    float c = 300;          // m/s
    float MaxSimTime = 0.5;   // second

    std::cout << "Program started" << std::endl;
      

    while ((opt = getopt(argc, argv, "n:c:")) != -1)
    {
        //std::cout << opt << "-->" << optarg << std::endl;
        switch (opt)
        {
        case 'n':
            //std::cout << "in" << std::endl;
            N = atoi(optarg);
            Ntot = N + 2; //nombre de noeuds incluant imaginaires
            std::cout << "n = " << N << std::endl;
            break;
        
        case 'c':
            CFL = std::stof(optarg);
            std::cout << "CFL = " << CFL << std::endl;
            break;

        default:
            break;
        }
    }
    
    BackSolver back = BackSolver(L, Ntot, CFL, c);
    back.solve(MaxSimTime);
    
    FrontSolver front = FrontSolver(L, Ntot, CFL, c);
    front.solve(MaxSimTime);

    MidSolver mid = MidSolver(L, Ntot, CFL, c);
    mid.solve(MaxSimTime);


    return 0;
}