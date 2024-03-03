#include <fstream>
#include <iostream>
#include <cmath>

#define beta 0.001
#define N 500
#define gamma 0.1
#define TOL 10e-6
#define delta_t 0.1

using namespace std;

double f(double u)
{
    return (beta * N - gamma) * u - beta *u *u;
}
double df(double du)
{
    return (beta * N - gamma) - 2 * beta * du;
}

int main()
{
    fstream plik_1;
    fstream plik_2;
    fstream plik_3;
    plik_1.open("picard.txt",ios::out);
    plik_2.open("newton.txt",ios::out);
    plik_3.open("rk2.txt", ios::out);
    // zmienne dla metody Picarda
    double u = 1;
    double u1;

    //zmienne dla iteracji Newtona
    double un = 1;
    double u1n;
    
    //zmienne do zadania 2
    double c1 = 0.5 - sqrt(3) / 6.;
    double c2 = 0.5 + sqrt(3) / 6.;
    double a1_1 = 0.25;
    double a1_2 = 0.25-sqrt(3) / 6.;
    double a2_2 = 0.25;
    double a2_1 = 0.25-sqrt(3) / 6.;
    double b2;
    double b1 = b2 = 0.5;
    double u_1, u_2,ur=1;
    double delta_u_1, delta_u_2;
    double m_11, m_12, m_21, m_22;
    double f_1, f_2;

    double t, n;
    int i; // numer iteracji

    //zadanie 1
    for (t = 0; t < 100;t+=delta_t){

        //warunki początkowe
        u1 = u;
        u1n = un;
        u_1=u_2 = ur;
        //Metoda Picarda
        for (i = 0; i <= 20; i++)
        {  
            u1 = u + delta_t / 2. * (f(u) + f(u1));
            if ((u1 - u) < TOL)
                break;
        }
         //iteracja Newtona
          for (i = 0; i <= 20; i++)
        {
            u1n = u1n - (u1n-un-delta_t / 2. * (f(un) + f(u1n)))/(1-delta_t/2.*df(u1n));
            if ((u1n - un) < TOL)
                break;
        }
        //zadanie 2
          for (i = 0; i <= 20; i++)
        {
            f_1 = u_1 - ur - delta_t*(a1_1 * f(u_1) + a1_2 * f(u_2));
            f_2 = u_2 - ur - delta_t*(a2_1 * f(u_1) + a2_2 * f(u_2));

            m_11 = 1 - delta_t * a1_1 * df(u_1);
            m_12=- delta_t * a1_2 * df(u_2);
            m_21=- delta_t * a2_1 * df(u_1);
            m_22 = 1 - delta_t * a2_2 * df(u_2);

            delta_u_1 = (f_2 * m_11 - f_1 * m_22) / (m_11 * m_22 - m_12 * m_21);
            delta_u_2 = (f_1 * m_21 - f_2 * m_11) / (m_11 * m_22 - m_12 * m_21);
            
            u_1 = u_1 + delta_u_1;
            u_2 = u_2 + delta_u_2;

        }
        //metoda picarda
        u = u + delta_t / 2. * (f(u) + f(u1));
        plik_1 << t << "\t" << u << "\t" << (N - u) <<endl;
       
        //iteracja Newtona
        un = un + delta_t / 2. * (f(un) + f(u1n));
        plik_2 << t << "\t" << un << "\t" << (N - un) <<endl;
        
        //zadanie2
        ur = ur + delta_t / 2. * (f(u_1) + f(u_2));
        plik_3 << t << "\t" << ur << "\t" << (N - ur) <<endl;
    }
   
}