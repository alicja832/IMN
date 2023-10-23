#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#define lambda -1
#define R 100
#define L 0.1
#define C 0.001

using namespace std;
double w_v;
/**
 * @brief 
 * dy/dt
 * funkcja używana do zadania pierwszego
 * @param y 
 * @return double 
 */
double fun(double y)
{
    
    return lambda*y;
}
/**
 * @brief 
 * funkcja zwracająca aktualną wartość napięcia w danej chwili dla zadanej częstotliwości
 * @param w 
 * @param t 
 * @return double 
 */
double V(double w,double t)
{
    return 10*sin(w*t);
}
/**
 * @brief 
 * dQ/dt
 * @param t 
 * @param Q 
 * @param I 
 * @return double 
 */
double f(double t,double Q, double I)
{
    return I;
}
/**
 * @brief 
 * dI/dt
 * @param t 
 * @param Q 
 * @param I 
 * @return double 
 */
double g(double t,double Q, double I)
{
    return V(w_v,t)/L-R/L*I-1/(L*C)*Q;
}



int main()
{
    /**
     * @brief 
     * zadanie pierwsze
     * generacja danych do wykresu
     */
    {
        fstream plik1_1;
        fstream plik1_2;
        fstream plik1_3;
        //y-schemat eulera
        //y_t-metoda trapezów
        double y,y_t,t,n,y_num,k1=0,k2=0,k1n,k2n,k3,k4,y_t2;
        for(t=0.01;t<=5;t*=10)
        {
            y=1;
            y_t=1;
            y_t2=1;
            plik1_1.open("wynik"+to_string(t)+".txt",ios::out);
            plik1_2.open("wynik1.2:"+to_string(t)+".txt",ios::out);
            plik1_3.open("wynik1.3:"+to_string(t)+".txt",ios::out);
            for(n=0;n<=5/t;n++)
            {
                /**
                 * @brief 
                 * schemat eulera
                 */
                y_num=exp(lambda*t*n);

                plik1_1<<n*t<<"\t";
                plik1_1<<y<<"\t";
                plik1_1<<y_num<<"\t";
                plik1_1<<y-y_num<<endl;
                
                y=y+t*fun(y);
                
                //metoda jawna trapezów
                plik1_2<<n*t<<"\t";
                plik1_2<<y_t<<"\t";
                plik1_2<<y_num<<"\t";
                plik1_2<<y_t-y_num<<endl;
                k1=fun(y_t);
                k2=fun(y_t+t*k1);
                y_t=y_t+t/2.0*(k1+k2);

                //metoda jawna RK4
                plik1_3<<n*t<<"\t";
                plik1_3<<y_t2<<"\t";
                plik1_3<<y_num<<"\t";
                plik1_3<<y_t2-y_num<<endl;
                k1n=fun(y_t2);
                k2n=fun(y_t2+t/2.0*k1n);
                k3=fun(y_t2+t/2.0*k2n);
                k4=fun(y_t2+t*k3);
                y_t2=y_t2+t/6.*(k1n+2*k2n+2*k3+k4);

                }
            plik1_1.close();
            plik1_2.close();
            plik1_3.close();

     
        }
    }
    //zadanie 2
    {
        fstream plik_Q;
        fstream plik_I;
        
        
        double w_0=1./sqrt(L*C);
        double T=2*M_PI/w_0;
        double Q=0,I=0;
        double t=10e-4,n;
        double k1Q,k2Q,k3Q,k4Q,k1I,k2I,k3I,k4I;
        vector<double> ww{0.5*w_0,0.8*w_0,1.0*w_0,1.2*w_0};

        for(auto w:ww){

            plik_Q.open("wynikQ"+to_string(int(w))+".txt",ios::out);
            plik_I.open("wynikI"+to_string(int(w))+".txt",ios::out);
            
            for(n=0;n<=4*T/t;n++)
            {
                plik_Q<<n*t<<"\t";
                plik_Q<<Q;
                plik_Q<<std::endl;
                plik_I<<n*t<<"\t";
                plik_I<<I<<std::endl;
                k1Q=f(n*t,Q,I);
                k1I=g(n*t,Q,I);
                k2Q=I+t/2.0*k1I;
                k2I=V(w,t*(n+0.5))/L-1/(L*C)*(Q+t/2.*k1Q)-R/L*(I+t/2.*k1I);
                k3Q=I+t/2.*k2I;
                k3I=V(w,t*(n+0.5))/L-1/(L*C)*(Q+t/2.*k2Q)-R/L*(I+t/2.*k2I);
                k4Q=I+t*k3I;
                k4I=V(w,t*(n+0.5))/L-1/(L*C)*(Q+t*k3Q)-R/L*(I+t*k3I);

                Q=Q+t/6.*(k1Q+2*k1Q+2*k3Q+k4Q);
                I=I+t/6.*(k1I+2*k1I+2*k3I+k4I);
            }
            plik_I.close();
            plik_Q.close();

        }

   
    }
}