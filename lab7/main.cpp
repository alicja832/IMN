#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#define IT_MAX 20000

//parametry potrzebne do obliczen
double delta=0.01;
double ro=1,ni=1;
int i1=50,j1=55;
int nx=200,ny=90;

//funkcja sprawdzajaca czy dane wspolrzedne nie sa w brzegu
bool contains(int& i,int& j)
{
    if(i<=i1 && j<=j1)
    {
        return true;
    }
    return false;   
}

void pierwsze_wb(std::vector<std::vector<double>>& v,double q_we)
{   
    double y,i,j;
    double q_wy=q_we*((delta*ny*delta*ny*delta*ny)-(delta*j1*delta*j1*delta*j1)-3*(delta*j1*delta*ny*delta*ny)+3*(delta*j1*delta*j1*delta*ny))/(delta*ny*delta*ny*delta*ny);
    //brzeg A
    for(j=j1;j<=ny;j++)
    {
        y=j*delta;
        v[0][j]=q_we/(2*ni)*((y*y*y)/3.-(y*y)/2.*(j1*delta+ny*delta)+y*(j1*delta*ny*delta));
    }
    //brzeg C
     for(j=0;j<=ny;j++)
    {
        y=j*delta;
        v[nx][j]=q_wy/(2*ni)*(y*y*y/3.-y*y/2.*(ny*delta))+(q_we*delta*j1*delta*j1*(-j1*delta+3*ny*delta))/(12*ni);
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
    for(j=1;j<=j1;j++)
    {
        v[i1][j]=v[0][j1];
    }
    //brzeg F
    for(i=1;i<=i1;i++)
    {
        v[i][j1]=v[0][j1];
    }
}
void drugie_wb(std::vector<std::vector<double>>& v,std::vector<std::vector<double>>& z,double q_we)
{
    //y=delta*j
    double y,i,j;
    double q_wy=q_we*((delta*ny*delta*ny*delta*ny)-(delta*j1*delta*j1*delta*j1)-3*(delta*j1*delta*ny*delta*ny)+3*(delta*j1*delta*j1*delta*ny))/(delta*ny*delta*ny*delta*ny);
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
        v[nx][j]=q_wy/(2*ni)*(2*y-delta*ny);
    }
    //brzeg B
    for(i=1;i<nx;i++)
    {
        v[i][ny]=2./(delta*delta)*(z[i][ny-1]-z[i][ny]);
    }
    
    //brzed D
    for(i=(i1+1);i<nx;i++)
    {
        v[i][0]=2./(delta*delta)*(z[i][1]-z[i][0]);
    }
    //brzeg E
    for(j=1;j<(j1);j++)
    {
        v[i1][j]=2./(delta*delta)*(z[i1+1][j]-z[i1][j]);
    }
    //brzeg F
    for(i=1;i<=i1;i++)
    {
        v[i][j1]=2./(delta*delta)*(z[i][j1+1]-z[i][j1]);
    }

    v[i1][j1]=0.5*(v[i1-1][j1]+v[i1][j1-1]);
}

int main()
{
    //nazwy, aby sie nie mylilo ksi z psi
    std::vector<std::vector<double>> pierwszy;
    pierwszy.resize(nx+1, std::vector<double>(ny+1, 0));
    std::vector<std::vector<double>> drugi;
    drugi.resize(nx+1, std::vector<double>(ny+1, 0));
    
    double q_we[]={-1000.,-4000,4000};
    double omega,tau;
    std::fstream plik_1[3];
    plik_1[0].open("wyn.dat",std::ios::out);
    plik_1[1].open("wyn_Qm4000.dat",std::ios::out);
    plik_1[2].open("wyn_Q4000.dat",std::ios::out);
    double u,v;
    int i,j,it,j2=j1+2;
    
    for(int k=0;k<3;k++)
    {
        for(i=0; i<=nx;i++)
            for(j=0;j<=ny;j++)
                {
                    pierwszy[i][j] = 0.;
                    drugi[i][j] = 0.;
                }
        
        //zaimplementowac algorytm relaksacji rownan ns
        pierwsze_wb(pierwszy,q_we[k]);
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
                    
                    if(!contains(i,j))
                    {
                        pierwszy[i][j]=0.25*(pierwszy[i+1][j]+pierwszy[i-1][j]+pierwszy[i][j+1]+pierwszy[i][j-1]
                            -delta*delta*drugi[i][j]);
                        drugi[i][j]=0.25*(drugi[i+1][j]+drugi[i-1][j]+drugi[i][j+1]+drugi[i][j-1])
                            -omega*ro/(16.0*ni)*((pierwszy[i][j+1]-pierwszy[i][j-1])*(drugi[i+1][j]-drugi[i-1][j])-(pierwszy[i+1][j]-pierwszy[i-1][j])*(drugi[i][j+1]-drugi[i][j-1]));
                    }
                }
                drugie_wb(drugi,pierwszy,q_we[k]);
        }
        for(i=1; i<nx;i++)
        {
            for(j=1;j<ny;j++)
                {   
                    if(contains(i,j))
                    {
                        pierwszy[i][j]=pierwszy[0][j1];
                        drugi[i][j]=drugi[0][j1];
                        u=0;
                        v=0;
                    }
                    else
                    {
                        u=1./(2*delta)*(pierwszy[i][j+1]-pierwszy[i][j-1]);
                        v=-1./(2*delta)*(pierwszy[i+1][j]-pierwszy[i-1][j]);
                    }
                    plik_1[k] << i * delta << "\t" << j * delta << "\t" << pierwszy[i][j]<<"\t"<<drugi[i][j]<<"\t";
                    if(k!=2)
                        plik_1[k]<<u<<"\t"<<v<<std::endl;
                    else
                    {
                        plik_1[k]<<std::endl;
                    }

                }
            plik_1[k]<<std::endl;
        }
      plik_1[k].close();
    }

    return 0;
}
