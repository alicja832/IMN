#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define IT_MAX 10000

int nx=400,ny=90,i1=200,i2=210;
int jx=50;
double delta=0.01,o=10.*delta,xa=0.45, ya=0.45;

using namespace std;

int main()
{
    double v[nx+1][ny+1];
    double vx[nx+1][ny+1];
    double vy[nx+1][ny+1];
    double vmax=0,vtmp=0; 
    double tmax=IT_MAX*delta;
    int przedzial=IT_MAX/5;
    //pierwsza czesc zadania
    fstream f_str;
    fstream plik_v;
    //druga czesc zadania
    fstream plik_u[2];
    fstream c[2];

    //zmienne pomocnicze do stworzenia map predkosci
    int a,b,con=IT_MAX/50;
    int i,j,k,it,l;
    
    //parametry do rownania AD
    double deltat,xsr=0.,calka=0.;
    vector<double> D={0.,0.1};
    double u0[nx+1][ny+1];
    double u1[nx+1][ny+1];

    //mapy predkosci
    f_str.open("psi.dat");
    plik_v.open("v.dat",ios::out);

    if(!f_str.is_open())
        exit(-1);

    for(i=0;i<=nx;i++)
        for(j=0;j<=ny;j++)
            f_str>>a>>b>>v[i][j];
    
    for(i=0;i<=nx;i++)
        for(j=0;j<=ny;j++)
    {
            vx[i][j]=0;
            vy[i][j]=0;
    }

    for(i=1;i<nx;i++)
    {
        for(j=1;j<ny;j++)
        {
           
            vx[i][j]=(v[i][j+1]-v[i][j-1])/(2*delta);
            vy[i][j]=-(v[i+1][j]-v[i-1][j])/(2*delta);
        
        }
       
    }
   
     //zastawka
    for(i=0;i<=nx;i++)
    {
        for(j=0;j<=ny;j++)
        {
                if((i>=i1 && i<=i2 && j<=jx) || i==0 || j==0 || i==nx || j==ny )
                {
                   

                    if(i>=i1 && i<=i2 && j<=jx)
                    {
                        vx[i][j]=0;
                        vy[i][j]=0;
                    }
                       //lewy brzeg
                   
                    //dolny
                    if((j==0) && (i!=0) && (i!=nx))
                    {
                        vx[i][j]=0;
                    }
                    //gorny
                    if((j==ny) && (i!=0) && (i!=nx))
                    {
                        vy[i][j]=0;
                    }
                     if(i==0)
                    {   
                    vx[0][j]= vx[1][j];
                    }
                    //prawy brzeg
                    if(i==nx)
                    {   
                    vx[i][j]=vx[nx-1][j];
                    }
                   
                }
                plik_v<<i<<"\t"<<j<<"\t"<<vx[i][j]<<"\t"<< vy[i][j]<<endl;
                vtmp= sqrt(vx[i][j]* vx[i][j]+ vy[i][j]* vy[i][j]);
                if(vtmp>vmax && i>0 && i<nx) vmax=vtmp;
        }
        plik_v<<endl;
    }
    f_str.close();
    plik_v.close();

    deltat=delta/(4.*vmax);
    
    
        c[0].open("ct_d0.dat",ios::out);
        c[1].open("ct_d01.dat",ios::out);
    
        plik_u[0].open("u_t_d0.dat",ios::out);
        plik_u[1].open("u_t_d01.dat",ios::out);
       
    
    
    //najpierw dla D=0(brak dysfuzji), D=1(z dyfuzją)
    for(l=0;l<2;l++)
    {
        for(i=0;i<=nx;i++)
            for(j=0;j<=ny;j++)
                {
                    //to jest ok
                    u0[i][j]=1./(2.*M_PI*o*o)*exp(-((delta*i-xa)*(delta*i-xa)+(delta*j-ya)*(delta*j-ya))/(2.*o*o));
                }    
        for(it=1;it<=IT_MAX;it++)
        {
            for(i=0;i<=nx;i++)
                for(j=0;j<=ny;j++)
                    u1[i][j]=u0[i][j];
            
            for(k=1;k<=20;k++)
                for(i=0;i<=nx;i++)
                    for(j=1;j<ny;j++)
                    {
                        if(i>=i1 && i<=i2 && j<=jx)
                            continue;
                        else if(i==0 || i==nx)
                        {
                            if(i==0)
                            {
                                //w miejscu gdzie się jest u[i-1][j] uzywam u[nx][j]
                                u1[i][j]=(1./(1.0+(2.*D[l]*deltat)/(delta*delta)))*
                                (
                                    u0[i][j]-deltat/2.*vx[i][j]*((u0[i+1][j]-u0[nx][j])/(2.*delta)+((u1[i+1][j]-u1[nx][j])/(2.*delta)))
                                    -deltat/2.*vy[i][j]*((u0[i][j+1]-u0[i][j-1])/(2*delta)+((u1[i][j+1]-u1[i][j-1])/(2*delta)))
                                    +deltat/2.*D[l]*(
                                        (u0[i][j+1]+u0[i][j-1]+u0[i+1][j]+u0[nx][j]-4.*u0[i][j])/(delta*delta)
                                        + ((u1[i][j+1]+u1[i][j-1]+u1[i+1][j]+u1[nx][j])/(delta*delta))
                                    )
                                );
                            }
                            
                            //w miejscu gdzie się jest u[i+1][j] uzywam u[0][j]
                            if(i==nx)
                                {
                                    u1[i][j]=(1./(1.0+(2.*D[l]*deltat)/(delta*delta)))*
                                    (
                                        u0[i][j]-deltat/2.*vx[i][j]*((u0[0][j]-u0[i-1][j])/(2.*delta)+((u1[0][j]-u1[i-1][j])/(2.*delta)))
                                        -deltat/2.*vy[i][j]*((u0[i][j+1]-u0[i][j-1])/(2*delta)+((u1[i][j+1]-u1[i][j-1])/(2*delta)))
                                        +deltat/2.*D[l]*(
                                            (u0[i][j+1]+u0[i][j-1]+u0[0][j]+u0[i-1][j]-4.*u0[i][j])/(delta*delta)
                                            + ((u1[i][j+1]+u1[i][j-1]+u1[0][j]+u1[i-1][j])/(delta*delta))
                                        )
                                    );   
                                }
                              
                        }
                        else if(i!=0 && i!=nx)
                        {
                             u1[i][j]=(1./(1.0+(2.*D[l]*deltat)/(delta*delta)))*
                                (
                                    u0[i][j]-deltat/2.*vx[i][j]*((u0[i+1][j]-u0[i-1][j])/(2.*delta)+((u1[i+1][j]-u1[i-1][j])/(2.*delta)))
                                    -deltat/2.*vy[i][j]*((u0[i][j+1]-u0[i][j-1])/(2.*delta)+((u1[i][j+1]-u1[i][j-1])/(2.*delta)))
                                    +deltat/2.*D[l]*(
                                        (u0[i][j+1]+u0[i][j-1]+u0[i+1][j]+u0[i-1][j]-4.*u0[i][j])/(delta*delta)
                                        + (u1[i][j+1]+u1[i][j-1]+u1[i+1][j]+u1[i-1][j])/(delta*delta)
                                    )
                                );   
                        }
                        
                    }
                    //koniec iteracji Picarda
            for(i=0;i<=nx;i++)
                for(j=0;j<=ny;j++)
                    u0[i][j]=u1[i][j];
            
            calka=0.;
            xsr=0.;
            
            for(i=0;i<=nx;i++)
            {
                for(j=0;j<=ny;j++)
                {
                    calka+=u0[i][j]*delta*delta;
                    xsr+=delta*i*u0[i][j]*delta*delta;
                }
            }
            c[l]<<it*deltat<<"\t"<<calka<<"\t"<<xsr<<endl;
           
             if(it%przedzial==0)
            {
                for(i=0;i<=nx;i++)
                {
                    for(j=0;j<=ny;j++)
                        plik_u[l]<<i<<"\t"<<j<<"\t"<<u0[i][j]<<endl;
                    plik_u[l]<<endl;
                }
                plik_u[l]<<endl;
                plik_u[l]<<endl;
            }
        
        }
        c[l].close();
        plik_u[l].close();
    }
   
}