#include <fstream>
#include <iostream>
#include <cmath>

#define lambda -1

using namespace std;

double fun(double y)
{
    
    return lambda*y;
}

int main()
{
    /**
     * @brief 
     * zadanie pierwsze
     * generacja danych do wykresu
     */
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
        plik1_1.open("wynik"+to_string(t)+".txt",std::ios::out);
        plik1_2.open("wynik1.2:"+to_string(t)+".txt",std::ios::out);
        plik1_3.open("wynik1.3:"+to_string(t)+".txt",std::ios::out);
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
            plik1_1<<y-y_num<<std::endl;
            
            y=y+t*fun(y);
            
            //metoda jawna trapezów
            plik1_2<<n*t<<"\t";
            plik1_2<<y_t<<"\t";
            plik1_2<<y_num<<"\t";
            plik1_2<<y_t-y_num<<std::endl;
            k1=fun(y_t);
            k2=fun(y_t+t*k1);
            y_t=y_t+t/2.0*(k1+k2);

            //metoda jawna RK4
            plik1_3<<n*t<<"\t";
            plik1_3<<y_t2<<"\t";
            plik1_3<<y_num<<"\t";
            plik1_3<<y_t2-y_num<<std::endl;
            k1n=fun(y_t2);
            k2n=fun(y_t2+t/2.0*k1n);
            k3=fun(y_t2+t/2.0*k2n);
            k4=fun(y_t2+t*k3);
            y_t2=y_t2+t/6.*(k1n+2*k2n+2*k3+k4);

            }
        plik1_1.close();
        plik1_2.close();
        plik1_3.close();

        //zadanie2
    }


    
   
}