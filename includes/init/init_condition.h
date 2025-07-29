#pragma once
#include "Containers/ParticleContainer.h"
#include<random>
#include<cmath>
namespace InitialConditoin
{
    //double
    void set_exponential_disk(ParticleContainer<double>& ps,double solt, double R); //TODO: реализовать задание экспоненциального диска
    void set_circle_velocity(ParticleContainer<double>& ps,double M,double R);     
    void set_uniform_disk(ParticleContainer<double>& ps,double solt, double R);    

    //long double
    void set_exponential_disk(ParticleContainer<long double>& ps, long double solt, long double R);           //TODO: реализовать задание экспоненциального диска
    void set_circle_velocity(ParticleContainer<long double>& ps,long double M,long double R);                        
    void set_uniform_disk(ParticleContainer<long double>& ps, long double solt, long double R);    
}