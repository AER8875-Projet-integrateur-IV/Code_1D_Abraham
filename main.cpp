// Your First C++ Program

#include <iostream>
//#include <fstream>
#include <stdlib.h>     /* atoi */
#include <unistd.h>
//#include <cstdlib>
//#include <string> 
#include "oneDwave.hpp"
#include "Plotter.hpp"

int main(int argc, char** argv) {
    int opt;
    int N = 100; 
    int Ntot = N+2;
    float CFL = 1;
    float L = 100;          // m
    float c = 300;          // m/s
    float MaxSimTime = 10;   // second

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
    
    /*
    BackSolver back = BackSolver(L, Ntot, CFL, c, MaxSimTime);
    back.solve();
    
    FrontSolver front = FrontSolver(L, Ntot, CFL, c, MaxSimTime);
    front.solve();

    MidSolver mid = MidSolver(L, Ntot, CFL, c, MaxSimTime);
    mid.solve();
    */

    BackSolver back1 = BackSolver(L, Ntot, 1, c, MaxSimTime);
    back1.solve();

    BackSolver back2 = BackSolver(L, Ntot, 0.75f, c, MaxSimTime);
    back2.solve();

    BackSolver back3 = BackSolver(L, Ntot, 0.5f, c, MaxSimTime);
    back3.solve();

    int Nb_frame = 1000;
    float dt = MaxSimTime/Nb_frame;
    SimData data_ar[3] = {back1.get_data(), back2.get_data(), back3.get_data()};

    Plotter plot = Plotter(L, Nb_frame, N, dt, 3, data_ar);

    return 0;
}