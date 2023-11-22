#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

#define epsilon 1
#define delta 0.1 
#define nx 150
#define ny 100
#define v1 10.0
#define v2 0.0
#define xmax delta*nx
#define ymax delta*ny

double ro_1(double x,double y)
{
    double deltax=0.1*xmax;
    double deltay=0.1*ymax;

    x=delta*x;
    y=delta*y;

    return exp(-(x-0.35*xmax)*(x-0.35*xmax)/(deltax*deltax)-(y-0.5*ymax)*(y-0.5*ymax)/(deltay*deltay));

}
double ro_2(double x,double y)
{   
    double deltax=0.1*xmax;
    double deltay=0.1*ymax;
    x=delta*x;
    y=delta*y;

    return exp(-(x-0.65*xmax)*(x-0.65*xmax)/(deltax*deltax)-(y-0.5*ymax)*(y-0.5*ymax)/(deltay*deltay));;
}

//metoda relaksacji globalnej

/// @brief 
/// @return 
int main()
{
    int i,j,k;
    double omega_g[]={0.6,1.0};
    double  TOL=0.00000001;
    double sit=0.,sittmp=0;
    double wl[]={1.0,1.4,1.8,1.9};
    int nr=0;

    std::vector<std::vector<double>> vs;
    std::vector<std::vector<double>> vn;
    vs.resize(nx+1, std::vector<double>(ny+1, 0));
    vn.resize(nx+1, std::vector<double>(ny+1, 0));
    std::fstream lok[4];
    std::fstream glob[2];
    for(i=0;i<(nx+1);i++)
     {
        vs[i][0]=v1;
        vs[i][ny]=v2;
        vn[i][0]=v1;
        vn[i][ny]=v2;
     }
     double ro[nx+1][ny+1];
     for(i=0;i<(nx+1);i++)
        for(j=0;j<(ny+1);j++)
            ro[i][j]=ro_1(i,j)+ro_2(i,j);
  
     for(k=0;k<4;k++)
        
        { 
            nr=0;
            sit=0; 
             for(i=0;i<(nx+1);i++)
                {
                    for(j=0;j<(ny+1);j++)
                    {
                        vn[i][j]=0.;
                    }
                }
           
            for(i=0;i<(nx+1);i++)
                {
                    vs[i][0]=v1;
                    vs[i][ny]=v2;
                    vn[i][0]=v1;
                    vn[i][ny]=v2;
                }
            lok[k].open("lok_"+std::to_string(wl[k])+".txt",std::ios::out); 
            do
            {
            
                for(i=1;i<(nx);i++)
                {
                    for(j=1;j<(ny);j++)
                    {
                        vn[i][j]=(1-wl[k])*vn[i][j]+wl[k]*0.25*(vn[i+1][j]+vn[i-1][j]+vn[i][j-1]+vn[i][j+1]+(pow(delta,2)/epsilon)*ro[i][j]);
                    }
                }
                  for(int j=1; j<ny; j++)
                {
                    vn[0][j]=vn[1][j];
                    vn[nx][j]=vn[nx-1][j];
                }
        
                sittmp=sit;
                sit=0.;
                for(i=0;i<(nx);i++)
                {
                    for(j=0;j<(ny);j++)
                    {
                        sit=sit+pow(delta,2)*(0.5*( (vn[i+1][j]-vn[i][j])/delta*(vn[i+1][j]-vn[i][j])/delta)+0.5*((vn[i][j+1]-vn[i][j])/delta*(vn[i][j+1]-vn[i][j])/delta)-(ro[i][j]*vn[i][j]));
                    }
                }
                ++nr;
                lok[k]<<nr<<"\t"<<(sit)<<std::endl;
            }
            while(fabs((sit-sittmp)/sittmp)>=TOL);
            lok[k].close();
        }
}
