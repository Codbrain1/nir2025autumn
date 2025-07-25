#pragma once
#include<vector>
template<class T>
class Buff_posit
{
    public:
    T t;
    std::vector<T> x,y,z;
    std::vector<T> vx,vy,vz;
};
template<class T>
class Buff_conv_laws
{
    T t,E,P_module,L_module;
};