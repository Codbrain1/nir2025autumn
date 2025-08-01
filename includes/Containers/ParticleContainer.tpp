#pragma once
#include "Containers/ParticleContainer.h"

// for type double
template <>
class ParticleContainer<double>
{
   public:
    // fields
    std::vector<double> x, y, z;
    std::vector<double> vx, vy, vz;
    std::vector<double> m;
    std::vector<double> fx, fy, fz;
    double E;
    double Px, Py, Pz;
    double Lx, Ly, Lz;
    double t, dt;
    const double G = 1;
    int N;
    // methods

    // конструктор класса, N - число частиц, M - общая масса частиц, t1 -  начальное время
    ParticleContainer(int _N, double M, double t1);
    void SaveToFile_all(std::ofstream& positions, std::ofstream& conv_laws);
    void SaveToFile_positions(std::ofstream& positions);
    void SaveToFile_conv_laws(std::ofstream& conv_laws);
    void SaveToBinaryFile_all(std::ofstream& positions, std::ofstream& conv_laws);
    void SaveToBinaryFile_positions(std::ofstream& positions);
    void SaveToBinaryFile_conv_laws(std::ofstream& conv_laws);
};

// for long double
template <>
class ParticleContainer<long double>
{
   public:
    // fields
    std::vector<long double> x, y, z;
    std::vector<long double> vx, vy, vz;
    std::vector<long double> m;
    std::vector<long double> fx, fy, fz;
    long double E;
    long double Px, Py, Pz;
    long double Lx, Ly, Lz;
    long double t, dt;
    const long double G = 1L;
    int N;

    // methods

    // конструктор класса, N - число частиц, M - общая масса частиц, t1 -  начальное время
    ParticleContainer(int _N, long double M, long double t1);

    void SaveToFile_all(std::ofstream& positions, std::ofstream& conv_laws);
    void SaveToFile_positions(std::ofstream& positions);
    void SaveToFile_conv_laws(std::ofstream& conv_laws);

    void SaveToBinaryFile_all(std::ofstream& positions, std::ofstream& conv_laws);
    void SaveToBinaryFile_positions(std::ofstream& positions);
    void SaveToBinaryFile_conv_laws(std::ofstream& conv_laws);
};
