#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#define delta 0.2
#define nx 128
#define ny 128
#define xmax delta*nx
#define ymax delta*ny
#define TOL 1E-8

using namespace std;
int main()
{
    vector<vector<double>> v;
    vector<int> zb_k={16,8,4,2,1};
    fstream plik[5];
    fstream plik_s[5];
    int i,j,l,k;
    double s,st;
    v.resize(nx+1, vector<double>(ny+1, 0));
    
    for(j=0;j<(ny+1);j++)
        v[0][j]= sin(M_PI*(j*delta/ymax));
    for(i=0;i<(nx+1);i++)
        v[i][ny]= -sin(2*M_PI*(i*delta/xmax));
    for(j=0;j<(ny+1);j++)
        v[nx][j]= sin(M_PI*(j*delta/ymax));
    for(i=0;i<(nx+1);i++)
        v[i][0]= sin(2*M_PI*(i*delta/xmax));
    for(int l=0;l<5;l++)
    {
        k=zb_k[l];
        plik[l].open("k"+to_string(k)+".txt",ios::out);
        plik_s[l].open("ks"+to_string(k)+".txt",ios::out);
        
        do{
             for(i=0;i<=(nx-k);i++)
            for(j=0;j<=(ny-k);j++)
            {
                v[i+k/2][j+k/2]=0.25*(v[i][j]+v[i+k][j]+v[i][j+k]+v[i+k][j+k]);
                v[i+k][j+k/2]=0.5*(v[i+k][j]+v[i+k][j+k]);
                v[i+k/2][j+k]=0.5*(v[i][j+k]+v[i+k][j+k]);
                v[i+k/2][j]=0.5*(v[i][j]+v[i+k][j]);
                v[i][j+k/2]=0.5*(v[i][j]+v[i][j+k]);
            }
            for(i=k;i<=(nx-k);i+=k)
                for(j=k;j<=(ny-k);j+=k)
                    v[i][j]=0.25*(v[i+k][j]+v[i-k][j]+v[i][j+k]+v[i][j-k]);
            
            st=s;
            s=0;
            for(i=0;i<=(nx-k);i+=k)
                for(j=0;j<=(ny-k);j+=k)
                {
                    s+=(k*delta)*(k*delta)/2*(pow((v[i+k][j]-v[i][j]+v[i+k][j+k]-v[i][j+k])/(2*k*delta),2)+pow((v[i][j+k]-v[i][j]+v[i+k][j+k]-v[i+k][j])/(2*k*delta),2));
                    plik_s[l]<<s<<endl;
                }
        }while(fabs(s-st)/st>=TOL);
        plik_s[l].close();
        //wpisujemy mape potencjalu
        for(i=0;i<(nx+1);i++)
            for(j=0;j<(ny+1);j++)
                plik[l]<<delta*i<<"\t"<<delta*j<<"\t"<<v[i][j]<<endl;
        plik[l].close();
        //zageszczanie siatki
        
        // for(i=0;i<=(nx-k);i++)
        //     for(j=0;j<=(ny-k);j++)
        //     {
        //         v[i+k/2][j+k/2]=0.25*(v[i][j]+v[i+k][j]+v[i][j+k]+v[i+k][j+k]);
        //         v[i+k][j+k/2]=0.5*(v[i+k][j]+v[i+k][j+k]);
        //         v[i+k/2][j+k]=0.5*(v[i][j+k]+v[i+k][j+k]);
        //         v[i+k/2][j]=0.5*(v[i][j]+v[i+k][j]);
        //         v[i][j+k/2]=0.5*(v[i][j]+v[i][j+k]);
        //     }
    }


}