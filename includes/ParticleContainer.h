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
    T t, dt;
    static constexpr T G=1L;

    //methods

    //конструктор класса, N - число частиц, M - общая масса частиц, t1 -  начальное время
    ParticleContainer(int N, T M,T t1):
    x(N,0), y(N,0), z(N,0),
    vx(N,0),vy(N,0),vz(N,0),
    m(N,M/(T)N),
    fx(N,0), fy(N,0), fz(N,0)
    {
        E=static_cast<T>(0);
        Px=Py=Pz=static_cast<T>(0);
        Lx=Ly=Lz=static_cast<T>(0);
        t=t1;
    }
    void SaveToFile_all();
    void SaveToFile_positions();
    void SaveToFile_conv_laws();
    void SaveToBinaryFile_all();
    void SaveToBinaryFile_positions();
    void SaveToBinaryFile_conv_laws();
    void SaveToFile_all_async();
    void SaveToBinaryFile_all_async();
};