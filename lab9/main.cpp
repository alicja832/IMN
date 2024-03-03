#include <iostream>
#include <fstream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h> 

//nie wiem co z tego ma wyjsc ale ma wyjsc okej,sprawdzic na taurusie
#define IT_MAX 2000

using namespace std;

int main()
{
    int nx=40, ny=40, N=(nx+1)*(ny+1);
    int i,j,l,k;
    double delta=1.,deltat=1.,Ta=40, Tb=0,Tc=30, Td=0,kb=0.1,kd=0.6;
    int signum;

    fstream plik_T;
    fstream plik_dT;
    plik_T.open("T.dat",ios::out);
    plik_dT.open("dT.dat",ios::out);

    gsl_permutation *perm=gsl_permutation_alloc(N);
    gsl_matrix *A = gsl_matrix_calloc(N, N);
    gsl_matrix *B = gsl_matrix_calloc(N, N);
    gsl_vector *T = gsl_vector_calloc(N);
    gsl_vector *Tn = gsl_vector_calloc(N);
    gsl_vector *c = gsl_vector_calloc(N);
    gsl_vector *d = gsl_vector_calloc(N);
    
    for(i=0;i<=(nx);i++)
    {
        for(j=0;j<=(ny);j++)
        {
            l=i+j*(nx+1);
            gsl_vector_set(T, l,0);
            if(i!=0 && i!=nx && j!=ny && j!=0)
            {
            
                gsl_matrix_set(A, l,l-nx-1,deltat/(2.*delta*delta));
                gsl_matrix_set(A, l,l-1,deltat/(2.*delta*delta));
                gsl_matrix_set(A, l,l+1,deltat/(2.*delta*delta));
                gsl_matrix_set(A, l,l+nx+1,deltat/(2.*delta*delta));

                
                gsl_matrix_set(B, l,l-nx-1,-deltat/(2.*delta*delta));
                gsl_matrix_set(B, l,l-1,-deltat/(2.*delta*delta));
                gsl_matrix_set(B, l,l+1,-deltat/(2.*delta*delta));
                gsl_matrix_set(B, l,l+nx+1,-deltat/(2.*delta*delta));

                gsl_matrix_set(A, l,l,-2.*deltat/(delta*delta)-1.);
                gsl_matrix_set(B, l,l,2.*deltat/(delta*delta)-1.);
            
            }
            else{
                
                if((i==0) || (i==nx))
                {
                    gsl_matrix_set(A, l,l,1);
                    gsl_matrix_set(B, l,l,1);
                    gsl_vector_set(c, l,0);
                    
                    if(i==0)
                    {
                        gsl_vector_set(T, l,Ta);
                    }
                    if(i==nx)
                    {
                        gsl_vector_set(T, l,Tc);
                    }
                }
                else if((j==ny) || (j==0))
                {
                    if (j==ny)
                    {
                        gsl_matrix_set(A, l,l-nx-1,-1./(kb*delta));
                        gsl_matrix_set(A, l,l,1+1./(kb*delta));
                        gsl_vector_set(c, l,Tb);
                    
                        for(k=0;k<ny;k++)
                            gsl_matrix_set(B, l,k,0);
                    }
                    if (j==0)
                    {
                        gsl_matrix_set(A, l,l,1+1./(kd*delta));
                        gsl_matrix_set(A, l,l+nx+1,-1./(kd*delta));
                        gsl_vector_set(c, l,Td);
                    
                    
                        for(k=0;k<ny;k++)
                            gsl_matrix_set(B, l,k,0);
                    }
                }
            }  
        }
    }

        gsl_linalg_LU_decomp(A,perm,&signum);

        for(k=0;k<=IT_MAX;k++)
        {
            gsl_blas_dgemv(CblasNoTrans,1,B,T,0,d);
            gsl_blas_daxpy(1,c,d);
            gsl_linalg_LU_solve(A,perm,d,T);

            if(k==100 || k==200 || k==500 || k==1000 || k==2000)
            {
                    for(i=0;i<=nx;i++)
                    {
                        for(j=0;j<=ny;j++)
                        {
                            l=i+j*(nx+1);
                            plik_T<<i<<"\t"<<j<<"\t"<<gsl_vector_get(T,l)<<endl;
                            if(l>0)
                                plik_dT<<i<<"\t"<<j<<"\t"<<(gsl_vector_get(T,l)-gsl_vector_get(Tn,l))/deltat<<endl;
                        }
                        plik_T<<endl;
                        plik_dT<<endl;
                    }
                    plik_dT<<endl;
                    plik_dT<<endl;
                    plik_T<<endl;
                    plik_T<<endl;
            }
            else if(k==99 || k==199 || k==499 || k==999 || k==1999)
                {
                    cout<<"l"<<endl;
                 for(l=0;l<N;l++)
                    {
                        gsl_vector_set(Tn,l,gsl_vector_get(T,l));
    
                    }
                }
        } 
        
    gsl_permutation_free( perm );
    gsl_vector_free(T); 
    gsl_matrix_free(A);
}
