#pragma once
#include<vector>
#include<fstream>
#include<iomanip>
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
    int N;
    static const T G;
    //methods

    //конструктор класса, N - число частиц, M - общая масса частиц, t1 -  начальное время
    ParticleContainer(int _N, T M,T t1);
    void SaveToFile_all(std::ofstream& positions, std::ofstream& conv_laws);
    void SaveToFile_positions(std::ofstream& positions);
    void SaveToFile_conv_laws(std::ofstream& conv_laws);

    void SaveToBinaryFile_all(std::ofstream& positions, std::ofstream& conv_laws); //TODO: реализовать сохранение в бинарные файлы
    void SaveToBinaryFile_positions(std::ofstream& positions);
    void SaveToBinaryFile_conv_laws(std::ofstream& conv_laws);
};
#include "../includes/ParticleContainer_impl.h"