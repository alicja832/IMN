#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

int main()
{
    fstream plikE[4];
    fstream plikU[4];
    
    int nx=150,nt=1000,n;
    double delta=0.1,deltat=0.05,xA=7.5,o=0.5,s,e,xf=2.5;
    double alfa,beta;
    std::vector<double> array_beta={0.,0.1,1.,1};
    std::vector<double> array_alfa={0.,0.,0.,1.};
    std::vector<double> u0(nx+1,0.),u (nx+1,0.),v(nx+1,0.),vp(nx+1,0.),a(nx+1,0.);
    int i,k;
   
  //zerowanie wszystkich tablic
  for(k=0;k<4;k++){

        beta=array_beta[k];
        alfa=array_alfa[k];
        if(k==3)
        {
            plikE[k].open("Ea"+to_string(alfa)+".txt",ios::out);
            plikU[k].open("Ua"+to_string(alfa)+".txt",ios::out);
        }
        else{
            plikE[k].open("E"+to_string(beta)+".txt",ios::out);
            plikU[k].open("U"+to_string(beta)+".txt",ios::out);
        }
        if(k!=0)
            for(i=0;i<=nx;i++)
            {
                u[i]=0.;
                u0[i]=0.;
                v[i]=0.;
                vp[i]=0.;
                a[i]=0.;
            }

        for(i=1;i<nx;i++)
        {
            u[i]=exp(-(i*delta-xA)*(i*delta-xA)/(2.*o*o));
        }
        for(i=0;i<=nx;i++)
        {
            u0[i]=u[i];
        }
        for(i=1;i<nx;i++)
        {
            a[i]=(u[i+1]-2.*u[i]+u[i-1])/(delta*delta)-beta*(u[i]-u0[i])
            /deltat+alfa*cos((50.*0*deltat)/((nt)*deltat))*xf;
        }

        for(n=0;n<nt;n++)
        {
            s=0.;
            for(i=1;i<nx;i++)
            {
                vp[i]=v[i]+deltat/2.*a[i];
                u0[i]=u[i];
                u[i]=u[i]+deltat*vp[i];
                a[i]=(u[i+1]-2.*u[i]+u[i-1])/(delta*delta)-beta*(u[i]-u0[i])
                /deltat+alfa*cos((50.*n*deltat)/((nt)*deltat))*xf;
                v[i]=vp[i]+deltat/2.*a[i];

                if(i!=nx && i!=0)
                    s+=v[i]*v[i]+pow((u[i+1]-u[i-1])/(2.*delta),2);

            }
            e=delta/4.*(pow((u[1]-u[0])/delta,2)+pow((u[nx]-u[nx-1])/delta,2))
                +delta/2.*s;
                //zapis do pliku e i u deltat*n
            plikE[k]<<n*deltat<<"\t"<<e<<endl;
            for(i=0;i<=nx;i++)
            {
                plikU[k]<<deltat*n<<"\t"<<delta*i<<"\t"<<u[i]<<endl;
            }
            plikU[k]<<endl;
        }
        plikU[k].close();
        plikE[k].close();
  }
  
}