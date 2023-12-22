#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h> 
//nie wiem co z tego ma wyjsc ale ma wyjsc okej
#define IT_MAX 2000

int main()
{
    int nx=40, ny=40, N=(nx+1)*(ny+1);
    int i,j,l;
    double delta=1.,deltat=1.,Ta=40, Tb=0,Tc=30, Td=0,kb=0.1,kd=0.6;

    gsl_matrix *A = gsl_matrix_calloc(N, N);
    gsl_matrix *B = gsl_matrix_calloc(N, N);
    gsl_vector *T = gsl_vector_calloc(N);
    gsl_vector *c = gsl_vector_calloc(N);
    gsl_vector *d = gsl_vector_calloc(N);
    
    for(i=1;i<(nx);i++)
        for(j=1;j<(ny);j++)
        {
            l=i+j*(nx+1);
            gsl_matrix_set(A, l,l-nx-1,deltat/(2.*delta*delta));
            gsl_matrix_set(A, l,l-1,deltat/(2.*delta*delta));
            gsl_matrix_set(A, l,l+1,deltat/(2.*delta*delta));
            gsl_matrix_set(A, l,l+nx+1,deltat/(2.*delta*delta));

            
            gsl_matrix_set(B, l,l-nx-1,-deltat/(2.*delta*delta));
            gsl_matrix_set(B, l,l-1,-deltat/(2.*delta*delta));
            gsl_matrix_set(B, l,l+1,-deltat/(2.*delta*delta));
            gsl_matrix_set(B, l,l+nx+1,-deltat/(2.*delta*delta));

            gsl_matrix_set(A, l,l,-2*deltat/(2.*delta*delta)-1);
            gsl_matrix_set(B, l,l,2.*deltat/(2.*delta*delta)-1);
            
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
            if((j==ny))
            {

                gsl_matrix_set(A, l,l-nx-1,-1./(kb*delta));
                gsl_matrix_set(A, l,l,1+1./(kb*delta));
                gsl_vector_set(c, l,Tb);
                
                for(k=0;k<ny;k++)
                    gsl_matrix_set(B, l,k,0);
            }
            if((j==0))
            {
                gsl_matrix_set(A, l,l,1+1./(kd*delta));
                gsl_matrix_set(A, l,l+nx+1,-1./(kd*delta));
                gsl_vector_set(c, l,Td);
                
                
                for(k=0;k<ny;k++)
                    gsl_matrix_set(B, l,k,0);
            }
        }
       
        gsl_permutation *perm=gsl_permutation_alloc(N);
        int signum=0;
        gsl_linalg_LU_decomp(A,perm,&signum);

        for(i=0;i<IT_MAX;i++)
        {
            gsl_blas_dgemv(CblasNoTrans,1,A,T,1,d);
            gsl_blas_daxpy(1,d,c);
            gsl_linalg_LU_solve(A,perm,d,T);
        }    
    gsl_permutation_free( perm );
    gsl_vector_free(T); 
    gsl_matrix_free(A);
}