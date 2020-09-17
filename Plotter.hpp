#ifndef PLOTTER_H
#define PLOTTER_H

#include "SimData.hpp" 

class Plotter
{
private:
    int Nb_frame;
    int Nb_noeuds;
public:
    Plotter();
    Plotter(float Length, int Nb_frame, int Nb_noeuds, float time_interval, int nb_data, SimData* data_ar);
};

#endif
