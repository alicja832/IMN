#include <fstream>
#include <iostream>
#include <string>
#include "mgmres.h"
int main()
{
    std::cout<<"dizal";
    double delta=0.1;
    int n[]={4,50,100,200};
    int nyy[]={4,50,100,200};
    int nx,ny;
    int ep1=1,ep2=ep1;
    double v[]={10,-10,10,-10};
    int i,j,l,k=-1,s;
    int brzeg=0;
   
    std::fstream plik;
    s=1;
    for(s=0;s<4;s++)
    {    nx=n[s];
        ny=nyy[s];
        k=-1;
        l=0;
        int N=(nx+1)*(ny+1);
        double **A=new double*[N];
        for(i=0;i<N;i++)
        {
            A[i]=new double [N];
        }
        //double A[N][N];
        double a[5*N]={0};//niezerowe wartosci elementow macierzowych
        int ja[5*N];//informacje o numerach kolumn
        int ia[N+1];//wskaznieki do elementow rozpoczynajacych dany wiersz 
        
        double b[N];
        double V[N];
        double epsilon[N];
        for(i=0;i<(nx+1);i++)
        {
            for(j=0;j<(ny+1);j++)
            {
                l=i+j*(nx+1);
                if(i<=(nx/2))
                    epsilon[l]=ep1;
                else
                    epsilon[l]=ep2;
            }
        }
        if(nx==4)
        {
            plik.open("6.b.txt",std::ios::out);
            plik<<"l"<<"\t"<<"i"<<"\t"<<"j"<<"\t"<<"b[l]"<<"\t"<<std::endl;
        }//wypelnienie macierzy a-elementy nie zerowe
        for(j=0;j<(ny+1);j++)
        {

            for(i=0;i<(nx+1);i++)
            {
                l=i+j*(nx+1);
                if(l-nx-1>=0)
                    A[l][l-nx-1]=epsilon[l]/(delta*delta);
                if(l-1>=0)
                    A[l][l-1]=epsilon[l]/(delta*delta);
                A[l][l]=-((2*epsilon[l]+epsilon[l+1]+epsilon[l+nx+1])/(delta*delta));
                if(l+1<N)
                    A[l][l+1]=epsilon[l+1]/(delta*delta);
                if((l+nx+1)<N)
                    A[l][l+nx+1]=epsilon[l+nx+1]/(delta*delta);
                brzeg=0;
                if(i==0)
                    {
                        brzeg=1;
                        b[l]=v[0];
                    }
                if(j==ny)
                    {
                        brzeg=1;
                        b[l]=v[1];
                    }
                if(i==nx)
                    {
                        brzeg=1;
                        b[l]=v[2];
                    }
                if(j==0)
                    {
                        brzeg=1;
                        b[l]=v[3];
                    }
                ia[l]=-1;
                if( (l- nx -1 )>=0 && brzeg==0)
                {
                    k++;
                    if(ia[l]<0)
                        ia[l]=k;
                    a[k]= A[l][l-nx-1];
                    ja[k]=l-nx-1;
                }
            if( (l-1 )>=0 && brzeg==0)
                {
                    k++;
                    if(ia[l]<0)
                        ia[l]=k;
                    a[k]= A[l][l-1];
                    ja[k]=l-1;
                }
                k++;
                if(ia[l]<0)
                    ia[l]=k;
                if(!brzeg)
                {
                    a[k]=A[l][l];
                }
                else
                {
                    a[k]=1;
                }
                ja[k]=l;
                if( (l )<N && brzeg==0)
                {
                    k++;
                    a[k]= A[l][l+1];
                    ja[k]=l+1;
                }
                if( (l-1 )>=0 && brzeg==0)
                {
                    k++;
                    a[k]= A[l][l+nx+1];
                    ja[k]=l+nx+1;
                }
            
            
            if(nx==4)
                plik<<l<<"\t"<<i<<"\t"<<j<<"\t"<<b[l]<<"\t"<<std::endl;

            }
        }
        k++;
      
        if(nx==4)
        {
            plik.close();
            plik.open("6.a.txt",std::ios::out);
            plik<<"k"<<"\t"<<"a[k]"<<std::endl;
        
                for(i=0;i<k;i++)
                    plik<<i<<"\t"<<a[i]<<std::endl;
            plik.close();
        }
        //zadanie 4-rozwiazywanie rownania
        int itr_max = 500, mr = 500;
        double tol_abs = 1E-8, tol_rel = 1E-8;
        pmgmres_ilu_cr(N-1,k,ia,ja,a,V,b,itr_max,mr,tol_abs,tol_rel);
        plik.open(std::to_string(nx)+".txt",std::ios::out);
        
        for(l=0;l<(N);l++)
        {
            j=l/(nx+1);
            i=l-j*(nx+1);
            plik<<i*delta<<"\t"<<j*delta<<"\t"<<V[l]<<std::endl;
        }
         plik.close();
         for(i=0;i<N;i++)
        {
            delete[] A[i];
        }
    delete[]A;
    }
}