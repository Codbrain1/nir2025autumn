#pragma once
#include<vector>
template<class T>
class Buff
{
    public:
    std::vector<T> x,y,z;
    std::vector<T> vx,vy,vz;
    T E,P_module,L_module;
};