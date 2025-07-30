#include "init/init_condition.h"

#include <cmath>
#include <random>
// реализация функций начального сосотояния для типа double
void InitialCondition::set_exponential_disk(ParticleContainer<double>& ps, double solt, double R) {}
void InitialCondition::set_circle_velocity(ParticleContainer<double>& ps, double M, double R)
{
    for (int i = 0; i < ps.N; ++i) {
        double r = sqrt(ps.x[i] * ps.x[i] + ps.y[i] * ps.y[i]);  // расстояние от частицы до центра координат
        double v_c = sqrt(ps.G * M * r) / R;                     // круговая скорость частицы

        // перевод в декартовы координаты
        ps.vx[i] = (r > 1e-12) ? -ps.y[i] * v_c / r : 0.0;
        ps.vy[i] = (r > 1e-12) ? ps.x[i] * v_c / r : 0.0;
        ps.vz[i] = 0;
    }
}
void InitialCondition::set_uniform_disk(ParticleContainer<double>& ps, double solt, double R)
{
    std::mt19937 gen(solt);                             // создание генератора чисел
    std::uniform_real_distribution<double> dist(0, R);  // задание равномерного распределения в диапазоне (0,R)
    double z_max = 0.2;
    double z_min = -0.2;
    for (int i = 0; i < ps.N; ++i) {
        double phi = dist(gen) * 2.0 * M_PI;
        double r = sqrt(dist(gen)) * R;

        ps.x[i] = r * cos(phi);
        ps.y[i] = r * sin(phi);
        ps.z[i] = z_min + (z_max - z_min) * dist(gen);
    }
}

// реализация функций начального сосотояния для типа long double
void InitialCondition::set_exponential_disk(ParticleContainer<long double>& ps, long double solt, long double R) {}
void InitialCondition::set_circle_velocity(ParticleContainer<long double>& ps, long double M, long double R)
{
    for (int i = 0; i < ps.N; ++i) {
        long double r = sqrtl(ps.x[i] * ps.x[i] + ps.y[i] * ps.y[i]);  // расстояние от частицы до центра координат
        long double v_c = sqrtl(ps.G * M * r) / R;                     // круговая скорость частицы

        // перевод в декартовы координаты
        ps.vx[i] = (r > 1e-15L) ? -ps.y[i] * v_c / r : 0.0L;
        ps.vy[i] = (r > 1e-15L) ? ps.x[i] * v_c / r : 0.0L;
        ps.vz[i] = 0L;
    }
}
void InitialCondition::set_uniform_disk(ParticleContainer<long double>& ps, long double solt, long double R)
{
    std::mt19937_64 gen(solt);                                // создание генератора чисел
    std::uniform_real_distribution<long double> dist(0L, R);  // задание равномерного распределения в диапазоне (0,R)
    long double z_max = 0.2L;
    long double z_min = -0.2L;
    for (int i = 0; i < ps.N; ++i) {
        long double phi = dist(gen) * 2.0L * M_PI;
        long double r = sqrtl(dist(gen)) * R;

        ps.x[i] = r * cosl(phi);
        ps.y[i] = r * sinl(phi);
        ps.z[i] = z_min + (z_max - z_min) * dist(gen);
    }
}