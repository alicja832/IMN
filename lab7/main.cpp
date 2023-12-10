#include <fstream>
#include <iostream>
#include <vector>
#define IT_MAX 2000

//parametry potrzebne do obliczen
double delta=0.01;
double ro=1,ni=1;
int i1=50,j1=55;
int nx=200,ny=90;

bool contains_i(int i)
{
    if(i!=i1 && i!=nx && i!=0)
    {
        return false;
    }
    return true;
}
bool contains_j(int j)
{
    if(j!=j1 && j!=ny && j!=0)
    {
        return false;
    }
    return true;
}

void pierwsze_wb(std::vector<std::vector<double>>& v,double q_we)
{   
    //y=delta*j
    double y,i,j;
    //brzeg A
    for(j=j1;j<=ny;j++)
    {
        y=j*delta;
        v[0][j]=q_we/(2*ni)*(y*y*y/3.-y*y/2.*(j1*delta+ny*delta)+y*(j1*delta*ny*delta));
    }
    //brzeg C
     for(j=j1;j<=ny;j++)
    {
        y=j*delta;
        v[nx][j]=q_we/(2*ni)*(y*y*y/3.-y*y/2.*(ny*delta))+(q_we*delta*j1*delta*j1*(-j1*delta+3*ny*delta))/(12*ni);
    }
    //brzeg B
    for(i=1;i<nx;i++)
    {
        v[i][ny]=v[0][ny];
    }
    
    //brzed D
    for(i=i1;i<nx;i++)
    {
        v[i][0]=v[0][j1];
    }
    //brzeg E
    for(j=1;i<j1;i++)
    {
        v[i1][i]=v[0][j1];
    }
    //brzeg F
    for(i=1;i<i1;i++)
    {
        v[i][j1]=v[0][j1];
    }
}
void drugie_wb(std::vector<std::vector<double>>& v,double q_we)
{
    //y=delta*j
    double y,i,j;
    //brzeg A
    for(j=j1;j<=ny;j++)
    {
        y=j*delta;
        v[0][j]=q_we/(2*ni)*(2*y-j1*delta-delta*ny);
    }
    //brzeg C
     for(j=0;j<=ny;j++)
    {
        y=j*delta;
        v[nx][j]=q_we/(2*ni)*(2*y-j1*delta-delta*ny);
    }
    //brzeg B
    for(i=1;i<nx;i++)
    {
        v[i][ny]=2/(delta*delta)*(v[i][ny-1]-v[i][ny]);
    }
    
    //brzed D
    for(i=(i1+1);i<nx;i++)
    {
        v[i][0]=2/(delta*delta)*(v[i][1]-v[i][0]);
    }
    //brzeg E
    for(j=1;j<(j1-1);j++)
    {
        v[i1][j]=2/(delta*delta)*(v[i1+1][j]-v[i1][j]);
    }
    //brzeg F
    for(i=1;i<i1;i++)
    {
        v[i][j1]=2/(delta*delta)*(v[i][j1+1]-v[i][j1]);
    }
    v[i1-1][j1]=0.5*(v[i1-1][j1]+v[i1][j1-1]);
}

int main()
{
    std::vector<std::vector<double>> pierwszy;
    pierwszy.resize(nx+1, std::vector<double>(ny+1, 0));
    std::vector<std::vector<double>> drugi;
    drugi.resize(nx+1, std::vector<double>(ny+1, 0));
    
    double q_we=-1000.,omega,tau;
    std::fstream plik;
    std::fstream plik2;
    int i,j,it,j2=j1+2;
    for(i=0; i<=nx;i++)
            for(j=0;j<=ny;j++)
                {
                    pierwszy[i][j] = 0.;
                    drugi[i][j] = 0.;
                }
    //zaimplementowac algorytm relaksacji rownan ns
    pierwsze_wb(pierwszy,q_we);
    plik.open("q1.txt",std::ios::out);
    plik2.open("q2.txt",std::ios::out);

    for(it=1;it<=IT_MAX;it++)
    {
        if(it<2000)
        {
            omega=0;
        }
        else
        {
            omega=1;
        }
        for(i=1; i<nx;i++)
            for(j=1;j<ny;j++)
            {
                if(!contains_i(i) && !contains_j(j))
                {
                    pierwszy[i][j]=0.25*(pierwszy[i+1][j]+pierwszy[i-1][j]+pierwszy[i][j+1]+pierwszy[i][j-1]
                        -delta*delta*drugi[i][j]);
                    drugi[i][j]=0.25*(drugi[i+1][j]+drugi[i-1][j]+drugi[i][j+1]+drugi[i][j-1])
                        -omega*ro/(16.0*ni)*((pierwszy[i][j+1]-pierwszy[i][j-1])*(drugi[i+1][j]-drugi[i-1][j])-(pierwszy[i+1][j]-pierwszy[i-1][j])*(drugi[i][j+1]-drugi[i][j-1]));
                }
            }
        drugie_wb(drugi,q_we);
        tau=0.;
        if(it<20)
        {
            for(i=1;i<nx;i++)
            {
                tau+=pierwszy[i+1][j2]+pierwszy[i-1][j2]+pierwszy[i][j2+1]+pierwszy[i][j2-1]-4*pierwszy[i][j2]-delta*delta*drugi[i][j2];
            }
            std::cout<<tau<<std::endl;
        }
    }
    for(i=0; i<=nx;i++)
            for(j=0;j<=ny;j++)
                if(pierwszy[i][j]<(-49)&& pierwszy[i][j]>(-56))
                plik << i * delta << "\t" << j * delta << "\t" << pierwszy[i][j]<<std::endl;
    for(i=0; i<=nx;i++)
            for(j=0;j<=ny;j++)
                if(drugi[i][j]<(400)&& drugi[i][j]>(-200))
                plik2 << i * delta << "\t" << j * delta << "\t" << drugi[i][j]<<std::endl;
    //zadanie 4, wykres konturowy psi, ksi
    plik.close();
    plik2.close();

    return 0;
}
