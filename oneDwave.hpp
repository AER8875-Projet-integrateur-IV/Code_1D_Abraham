#define ONEDWAVE_H
#include "SimData.hpp"

class oneDwave
{
protected:   
    SimData data;
    float dx;
    int Ntot;
    float dt;
    float CFL;
    float SimTime;
    void initialise_mesh();
    void fix_mesh_edge(int row);
    void Write_Array_2_File(std::string method, float time, int row);

public:
    float **mesh;
    oneDwave();
    oneDwave(float Length, int NumberOfKnots, float CFL_user, float velocity, float SimulationTime);

    SimData get_data();
};

class BackSolver: public oneDwave
{
public:
    BackSolver(float Length, int NumberOfKnots, float CFL_user, float velocity, float SimulationTime):oneDwave(Length, NumberOfKnots, CFL_user, velocity, SimulationTime){};
    void solve();
};

class FrontSolver: public oneDwave
{
public:
    FrontSolver(float Length, int NumberOfKnots, float CFL_user, float velocity, float SimulationTime):oneDwave(Length, NumberOfKnots, CFL_user, velocity, SimulationTime){};
    void solve();
};

class MidSolver: public oneDwave
{
public:
    MidSolver(float Length, int NumberOfKnots, float CFL_user, float velocity, float SimulationTime):oneDwave(Length, NumberOfKnots, CFL_user, velocity, SimulationTime){};
    void solve();
};


