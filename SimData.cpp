#include <iostream>
#include <cmath>
#include "SimData.hpp"

SimData::SimData(){}
SimData::SimData(float SimTime, int Nb_noeuds, float time_interval):SimData::SimData()
{
    nb_frame = static_cast<int>(SimTime/time_interval) + 1;
    N = Nb_noeuds;
    
    time_ar = new float[nb_frame];
    for(int i=0; i<nb_frame; i++)
    {
        time_ar[i] = time_interval*i;
    }

   // u = new float[nb_frame][N];

    u = new float*[nb_frame]; // dynamic array (size 2) of pointers to int
    for (int i = 0; i < nb_frame; ++i) 
    {
        u[i] = new float[N];
    // each i-th pointer is now pointing to dynamic array of actual int values
    }

    Current_index = 0;

}

void SimData::AddSolution(float *val)
{
    // val inclu les cellules fantomes  
    for(int i = 0; i<N; i++)
    {   
        u[Current_index][i] = val[i+1]; 
    }
    Current_index++;
}

void SimData::Interpolate_at_time_ar(float time, float *ar)
{
    int a_time_index;
    int b_time_index;

    for(int i=0; i<nb_frame; i++)
    {
        if(time_ar[i]<time)
        {
            a_time_index = i;
            b_time_index = i + 1;
        }
    }

    float a_time = time_ar[a_time_index];
    float b_time = time_ar[b_time_index];
    float a_val;
    float b_val;
    for(int i = 0; i<N; i++)
    {
        a_val = u[a_time_index][i];
        b_val = u[b_time_index][i];

        ar[i] = a_val + (b_time-a_time)/time * (b_val - a_val);
        
    }
}

float SimData::Interpolate_at_time_scalar(float time, int position_index)
{
    int a_time_index;
    int b_time_index;
    for(int i=0; i<nb_frame; i++)
    {
        if(time_ar[i]>time)
        {
            b_time_index = i;
            a_time_index = i - 1;
            break;
        }
    }

    float a_time = time_ar[a_time_index];
    float b_time = time_ar[b_time_index];
    float a_val = u[a_time_index][position_index];
    float b_val = u[b_time_index][position_index];

    float val = a_val + (b_time-a_time)/time * (b_val - a_val);

    return val;
}