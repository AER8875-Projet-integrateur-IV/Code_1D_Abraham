#include "Plotter.hpp"
#include "SimData.hpp"

#include <fstream>
#include <string> 
#include <cstdlib>
#include <iostream>

Plotter::Plotter(){}
Plotter::Plotter(float Length, int Nb_frame, int Nb_noeuds, float time_interval, int nb_data, SimData* data_ar):Plotter::Plotter()
{
    float current_time;
    float dx = Length / (Nb_noeuds-1);
    float u;

    std::string title = "./data/t.dat";
    std::ofstream myfile;
    myfile.open(title);
    myfile << "# X   Ui" << std::endl ;
    for (int t_index = 0; t_index < Nb_frame; t_index++)
    {
        current_time = t_index*time_interval;
        myfile << "# Time = " + std::to_string(current_time) << std::endl ;
        for (int x_index = 0; x_index < Nb_noeuds; x_index++)
        {            
            myfile << std::to_string((dx * x_index));
            for (int data_index = 0; data_index < nb_data; data_index++)
            {
                u = data_ar[data_index].Interpolate_at_time_scalar(current_time, x_index);
                myfile << " " << std::to_string(u);
            }
            myfile << std::endl;    
        }
        myfile << std::endl << std::endl;
    }

    myfile.close();

}