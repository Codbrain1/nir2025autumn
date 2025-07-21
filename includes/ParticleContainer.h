#pragma once
#include<vector>

template<class T>
class ParticleContainer
{
    public:
    //fields
    std::vector<T> x, y, z;
    std::vector<T> vx, vy, vz;
    std::vector<T> m;
    std::vector<T> fx, fy, fz;
    T E;
    T Px, Py, Pz; 
    T Lx, Ly, Lz;

    //methods
    void SaveToFile_all();
    void SaveToFile_positions();
    void SaveToFile_conv_laws();
    void SaveToBinaryFile_all();
    void SaveToBinaryFile_positions();
    void SaveToBinaryFile_conv_laws();
    void SaveToFile_all_async();
    void SaveToBinaryFile_all_async();
};