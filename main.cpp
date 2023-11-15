#include <iostream>
#include <vector>
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
vector<double> Rk2(double alfa,double t,double x,double v)
{
    //vector contains xn+1 and vn+1
    vector<double> rk;
    double k1x,k1v,k2x,k2v;

    k1x=f(x,v);
    k1v=g(alfa,x,v);

    k2x=f(x+t*k1x,v+t*k1v);
    k2v=g(alfa,x+t*k1x,v+t*k1v);

    rk.push_back(x+t/2.*(k1x+k2x));
    rk.push_back(v+t/2.*(k1v+k2v));

    return rk;
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
vector<double> trapeze_method(double alfa,double t,double x,double v)
{
    vector<double> tr;
    double x1=x,v1=v,deltax=0,deltav=0;
    double ff,gg,a11,a21,a12,a22;
    double psi=10e-10;

    x1=x+t/2.*(f(x,v)+f(x1,v1));
    v1=v+t/2.*(g(alfa,x,v)+g(alfa,x1,v1));

    ff=x1-x-t/2.*(f(x,v)+f(x1,v1));
    gg=v1-v-t/2.*(g(alfa,x,v)+g(alfa,x1,v1));

    while(abs(deltav)>=psi && abs(deltax)>=psi){

        a11=1;
        a12=-t/2.;
        a21=-t/2.*(-2*alfa*x1*v1-1);
        a22=1-t/2.*alfa*(1-(x1*x1));
        deltax=((-ff)*a22-(-gg)*a12)/(a11*a22-a12*a21);
        deltav=((-gg)*a11-(-ff)*a21)/(a11*a22-a12*a21);
        x1=x1+deltax;
        v1=v1+deltav;
    }
    tr.push_back(x1);
    tr.push_back(v1);


    return tr;
}

void time_pass_method(function<vector<double>(double,double,double,double)> fun,double TOL,string nazwa_pliku)
{
    double t=0,tmax=40,x0=0.01,v0=0,deltat0=1,alfa=5;
    double deltat=deltat0;
    double xn=x0,vn=v0;
    vector<double> result;
    double x21,v21,x22,v22,ex,ev;
    double S=0.75;
    fstream plik;
    plik.open(nazwa_pliku,ios::out);

    while(t<tmax){
        result=fun(alfa,deltat,xn,vn);
        result=fun(alfa,deltat,result[0],result[1]);
        x22=result[0];
        v22=result[1];
        //stawiamy jeden krok 2*t
        result=fun(alfa,2*deltat,xn,vn);
        x21=result[0];
        v21=result[1];
        //liczymy ex,ey
        ex=(x22-x21)/(2*2*2-1);
        ev=(v22-v21)/(2*2*2-1);

        if(max<double>(abs(ex),abs(ev))<TOL)
        {
            t=t+2*deltat;
            xn=x22;
            vn=v22;
            plik<<t<<"\t"<<vn<<"\t"<<xn<<"\t"<<deltat<<endl;
        }
        deltat=cbrt(S*TOL/max(abs(ex),abs(ev)))*deltat;

    }

}
int main()
{
    //algorytm numerycznego rozwiązywania różniczkowego z doborem kroku czasowego
    double tol[]={10e-2,10e-5};
    
    for(auto i: tol)
    {
        time_pass_method(Rk2,i,"rk2"+to_string(i)+".txt");
        time_pass_method(trapeze_method,i,"trapez"+to_string(i)+".txt");
    }

}