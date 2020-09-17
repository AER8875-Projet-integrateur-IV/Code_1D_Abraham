#ifndef SIMDATA_H
#define SIMDATA_H

class SimData
{
private:
    float *time_ar;
    float *distances;
    float **u;
    int N;
    int nb_frame;
    int Current_index;
public:
    SimData();
    SimData(float SimTime, int Nb_noeuds, float time_interval);

    void AddSolution(float *val);

    void Interpolate_at_time_ar(float time, float *ar);

    float Interpolate_at_time_scalar(float time, int position_index);
};

#endif


