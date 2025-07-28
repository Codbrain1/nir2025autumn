#pragma once
#include "Containers/ParticleContainer.h"
#include<random>
namespace InitialConditoin
{
    //double
    void set_exponential_disk(ParticleContainer<double>& ps,double solt); //TODO: реализовать задание экспоненциального диска
    void set_circle_velocity(ParticleContainer<double>& ps);               //TODO: реализовать задание круговых скоростей
    void set_uniform_disk(ParticleContainer<double>& ps,double solt);    //TODO: реадизовать задание равномерного диска

    //long double
    void set_exponential_disk(ParticleContainer<double>& ps,double solt);           //TODO: реализовать задание экспоненциального диска
    void set_circle_velocity(ParticleContainer<double>& ps);                        //TODO: реализовать задание круговых скоростей
    void set_uniform_disk(ParticleContainer<long double>& ps,long double solt);     //TODO: реадизовать задание равномерного диска    
}