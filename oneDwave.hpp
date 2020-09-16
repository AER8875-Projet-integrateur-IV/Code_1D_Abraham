#define ONEDWAVE_H

class oneDwave
{
//protected:  
public:  
    float dx;
    int Ntot;
    float dt;
    float CFL;
    void initialise_mesh();
    void fix_mesh_edge(int row);
    void Write_Array_2_File(std::string method, float time, int row);

public:
    float **mesh;
    oneDwave();
    oneDwave(float Length, int NumberOfKnots, float CFL_user, float velocity);
};

class BackSolver: public oneDwave
{
public:
    BackSolver(float Length, int NumberOfKnots, float CFL_user, float velocity):oneDwave(Length, NumberOfKnots, CFL_user, velocity){};
    void solve(float SimTime);
};

class FrontSolver: public oneDwave
{
public:
    FrontSolver(float Length, int NumberOfKnots, float CFL_user, float velocity):oneDwave(Length, NumberOfKnots, CFL_user, velocity){};
    void solve(float SimTime);
};

class MidSolver: public oneDwave
{
public:
    MidSolver(float Length, int NumberOfKnots, float CFL_user, float velocity):oneDwave(Length, NumberOfKnots, CFL_user, velocity){};
    void solve(float SimTime);
};


