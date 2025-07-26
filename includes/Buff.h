#pragma once
#include<vector>
template<class T>
class Buff_posit
{
    public:
    T t;
    int N;    
    std::vector<T> x,y,z;
    std::vector<T> vx,vy,vz;
};
template<class T>
class Buff_conv_laws
{
    public:
    T t,E,P_module2,L_module2;
};