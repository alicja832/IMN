#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

double f(double x,double v)
{
    return v;
}
double g(double alfa,double x,double v)
{
    return alfa*(1-x*x)*v-x;
}

/**
 * @brief 
 * 
 * @param alfa 
 * @param t - deltat 
 * @param x 
 * @param v 
 * @return vector<double> contains xn+1 and vn+1 
 */
void Rk2(double alfa,double t,double& x,double& v)
{
    double k1x,k1v,k2x,k2v;

    k1x=f(x,v);
    k1v=g(alfa,x,v);

    k2x=f(x+t*k1x,v+t*k1v);
    k2v=g(alfa,x+t*k1x,v+t*k1v);

    x=(x+t/2.*(k1x+k2x));
    v=(v+t/2.*(k1v+k2v));
}
/**
 * @brief 
 * 
 * @param alfa 
 * @param t - deltat 
 * @param x 
 * @param v 
 * @return vector<double> contains xn+1 and vn+1 
 */
void trapeze_method(double alfa,double t,double& x,double& v)
{
    double x1=x,v1=v,deltax=0,deltav=0;
    double ff,gg,a11,a21,a12,a22;
    double psi=1e-10;
    // x1=x+t/2.*(f(x,v)+f(x1,v1));
    // v1=v+t/2.*(g(alfa,x,v)+g(alfa,x1,v1));
   
    

    do{
        
        ff=x1-x-t/2.*(f(x,v)+f(x1,v1));
        gg=v1-v-t/2.*(g(alfa,x,v)+g(alfa,x1,v1));
        a11=1;
        a12=-t/2.;
        a21=-t/2.*(-2*alfa*x1*v1-1);
        a22=1-t/2.*alfa*(1-(x1*x1));
        deltax=((-ff)*a22-(-gg)*a12)/(a11*a22-a12*a21);
        deltav=((-gg)*a11-(-ff)*a21)/(a11*a22-a12*a21);
        x1=x1+deltax;
        v1=v1+deltav;
    }while(abs(deltav)>=psi || abs(deltax)>=psi);
    x=x1;
    v=v1;
}

void time_pass_method(function<void(double,double,double&,double&)> fun,double TOL,string nazwa_pliku)
{
    double t=0,tmax=40,x0=0.01,v0=0.,deltat0=1,alfa=5.;
    double deltat=deltat0;
    double xn=x0,vn=v0;
    double x21,v21,x22,v22,ex,ev;
    double S=0.75;
    fstream plik;

    plik.open(nazwa_pliku,ios::out);

    while(t<tmax){

        x22=xn;
        v22=vn;
        fun(alfa,deltat,x22,v22);
        fun(alfa,deltat,x22,v22);
            
        //stawiamy jeden krok 2*t
        x21=xn;
        v21=vn;
      
        fun(alfa,2*deltat,x21,v21);
       
        //liczymy ex,ey
        ex=(x22-x21)/(2*2-1);
        ev=(v22-v21)/(2*2-1);

        if(max<double>(abs(ex),abs(ev))<TOL)
        {
            t=t+2*deltat;
            xn=x22;
            vn=v22;
            plik<<t<<"\t"<<vn<<"\t"<<xn<<"\t"<<deltat<<endl;
        }
        deltat=cbrt(S*TOL/max<double>(abs(ex),abs(ev)))*deltat;

    }

}
int main()
{
    double tol[]={1e-2,1e-5};
    
    for(auto i: tol)
    {
        time_pass_method(Rk2,i,"rk2"+to_string(i)+".txt");
        time_pass_method(trapeze_method,i,"trapez"+to_string(i)+".txt");
    }

}