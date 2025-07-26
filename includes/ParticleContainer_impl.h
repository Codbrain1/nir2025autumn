//for type double
template<>
class ParticleContainer<double>
{
    public:
    //fields
    std::vector<double> x, y, z;
    std::vector<double> vx, vy, vz;
    std::vector<double> m;
    std::vector<double> fx, fy, fz;
    double E;
    double Px, Py, Pz; 
    double Lx, Ly, Lz;
    double t, dt;
    const double G=1;
    int N;
    //methods

    //конструктор класса, N - число частиц, M - общая масса частиц, t1 -  начальное время
    ParticleContainer(int _N, double M,double t1):
    x(_N,0), y(_N,0), z(_N,0),
    vx(_N,0), vy(_N,0), vz(_N,0),
    m(_N,M/static_cast<double>(_N)),
    fx(_N,0), fy(_N,0), fz(_N,0)
    {
        E = 0;
        Px=Py=Pz=0;
        Lx=Ly=Lz=0;
        t=t1;
        N=_N;
    }
    void SaveToFile_all(std::ofstream& positions, std::ofstream& conv_laws)
    {
        positions<<std::setprecision(13)<<t<<"\n";
        for(int i=0;i<N;++i)
        {
            positions<<x[i]<<"\t"<<y[i]<<"\t"<<z[i]<<"\t"
            <<vx[i]<<"\t"<<vy[i]<<vz[i]<<"\n";
        }
        // TODO: запись полной энергии и квадратов импульса и момента импульса системы
        conv_laws<<std::setprecision(13)<<t<<"\t"<<E<<"\t"<<Px*Px+Py*Py+Pz*Pz<<"\t"<<Lx*Lx+Ly*Ly+Lz*Lz<<"\n";

    }
    void SaveToFile_positions(std::ofstream& positions)
    {
        positions<<std::setprecision(13)<<t<<"\n";
        for(int i=0;i<N;++i)
        {
            positions<<x[i]<<"\t"<<y[i]<<"\t"<<z[i]<<"\t"
            <<vx[i]<<"\t"<<vy[i]<<vz[i]<<"\n";
        }
    }
    void SaveToFile_conv_laws(std::ofstream& conv_laws)
    {
        // TODO: запись полной энергии и квадратов импульса и момента импульса системы
        conv_laws<<std::setprecision(13)<<t<<"\t"<<E<<"\t"<<Px*Px+Py*Py+Pz*Pz<<"\t"<<Lx*Lx+Ly*Ly+Lz*Lz<<"\n";

    }

    void SaveToBinaryFile_all(std::ofstream& positions, std::ofstream& conv_laws)
    {
        positions.write(reinterpret_cast<char*>(&t),sizeof(double));
        for(int i=0;i<N;i++)
        {
            double posit[6]={x[i],y[i],z[i],vx[i],vy[i],vz[i]};
            positions.write(reinterpret_cast<const char*>(&posit),6*sizeof(double));
        }
        double convlaws[4]={t,E,Px*Px+Py*Py+Pz*Pz,Lx*Lx+Ly*Ly+Lz*Lz};
        conv_laws.write(reinterpret_cast<const char*>(&convlaws),4*sizeof(double));
    }
    void SaveToBinaryFile_positions(std::ofstream& positions)
    {
        positions.write(reinterpret_cast<char*>(&t),sizeof(double));
        for(int i=0;i<N;i++)
        {
            double posit[6]={x[i],y[i],z[i],vx[i],vy[i],vz[i]};
            positions.write(reinterpret_cast<const char*>(&posit),6*sizeof(double));
        }
    }
    void SaveToBinaryFile_conv_laws(std::ofstream& conv_laws){
        double convlaws[4]={t,E,Px*Px+Py*Py+Pz*Pz,Lx*Lx+Ly*Ly+Lz*Lz};
        conv_laws.write(reinterpret_cast<const char*>(&convlaws),4*sizeof(double));
    }
    
};

//for long double
template<>
class ParticleContainer<long double>
{
    public:
    //fields
    std::vector<long double> x, y, z;
    std::vector<long double> vx, vy, vz;
    std::vector<long double> m;
    std::vector<long double> fx, fy, fz;
    long double E;
    long double Px, Py, Pz; 
    long double Lx, Ly, Lz;
    long double t, dt;
    const long double G=1L;
    int N;

    //methods

    //конструктор класса, N - число частиц, M - общая масса частиц, t1 -  начальное время
    ParticleContainer(int _N, long double M,long double t1):
    x(_N,0L), y(_N,0L), z(_N,0L),
    vx(_N,0L), vy(_N,0L), vz(_N,0L),
    m(_N,M/static_cast<long double>(_N)),
    fx(_N,0L), fy(_N,0L), fz(_N,0L)
    {
        E = 0L;
        Px=Py=Pz=0L;
        Lx=Ly=Lz=0L;
        t=t1;
        N=_N;
    };
    
    void SaveToFile_all(std::ofstream& positions, std::ofstream& conv_laws)
    {

        positions<<std::setprecision(16)<<t<<"\n";
        for(int i=0;i<N;++i)
        {
            positions<<x[i]<<"\t"<<y[i]<<"\t"<<z[i]<<"\t"
            <<vx[i]<<"\t"<<vy[i]<<vz[i]<<"\n";
        }
        // TODO: запись полной энергии и квадратов импульса и момента импульса системы
        conv_laws<<std::setprecision(16)<<t<<"\t"<<E<<"\t"<<Px*Px+Py*Py+Pz*Pz<<"\t"<<Lx*Lx+Ly*Ly+Lz*Lz<<"\n";

    }
    void SaveToFile_positions(std::ofstream& positions)
    {
        positions<<std::setprecision(16)<<t<<"\n";
        for(int i=0;i<N;++i)
        {
            positions<<x[i]<<"\t"<<y[i]<<"\t"<<z[i]<<"\t"
            <<vx[i]<<"\t"<<vy[i]<<vz[i]<<"\n";
        }
    }
    void SaveToFile_conv_laws(std::ofstream& conv_laws)
    {
        // TODO: запись полной энергии и квадратов импульса и момента импульса системы
        conv_laws<<std::setprecision(16)<<t<<"\t"<<E<<"\t"<<Px*Px+Py*Py+Pz*Pz<<"\t"<<Lx*Lx+Ly*Ly+Lz*Lz<<"\n";

    }

    void SaveToBinaryFile_all(std::ofstream& positions, std::ofstream& conv_laws)
    {
        positions.write(reinterpret_cast<char*>(&t),sizeof(long double));
        for(int i=0;i<N;i++)
        {
            long double posit[6]={x[i],y[i],z[i],vx[i],vy[i],vz[i]};
            positions.write(reinterpret_cast<const char*>(&posit),6*sizeof(long double));
        }
        long double convlaws[4]={t,E,Px*Px+Py*Py+Pz*Pz,Lx*Lx+Ly*Ly+Lz*Lz};
        conv_laws.write(reinterpret_cast<const char*>(&convlaws),4*sizeof(long double));
    }
    void SaveToBinaryFile_positions(std::ofstream& positions)
    {
        positions.write(reinterpret_cast<char*>(&t),sizeof(long double));
        for(int i=0;i<N;i++)
        {
            long double posit[6]={x[i],y[i],z[i],vx[i],vy[i],vz[i]};
            positions.write(reinterpret_cast<const char*>(&posit),6*sizeof(long double));
        }
    }
    void SaveToBinaryFile_conv_laws(std::ofstream& conv_laws)
    {
        long double convlaws[4]={t,E,Px*Px+Py*Py+Pz*Pz,Lx*Lx+Ly*Ly+Lz*Lz};
        conv_laws.write(reinterpret_cast<const char*>(&convlaws),4*sizeof(long double));
    }
};