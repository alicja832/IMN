#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>


using namespace std;
int main()
{
    vector<vector<double>> v;
    double delta =0.2;
    double nx= 128;
    double ny= 128;
    double xmax =delta*nx;
    double ymax= delta*ny;
    double TOL =0.00000001;

    vector<int> zb_k={16,8,4,2,1};
    fstream plik[5];
    fstream plik_s[5];
    int i,j,l,k,it=0;
    double s,st;
    v.resize(nx+1, vector<double>(ny+1, 0));


    for(int l=0;l<5;l++)
    {


        for(int j=0 ;j<ny+1; j++)
        {
            v[0][j]=sin(M_PI*(j*delta/ymax));
            v[nx][j]=sin(M_PI*(j*delta/ymax));
        }
       
        for(int i=0 ;i<nx+1; i++)
        {
            v[i][ny]=-sin(2*M_PI*(i*delta/xmax));
            v[i][0]=sin(2*M_PI*(i*delta/xmax));
        }
        k=zb_k[l];
        plik[l].open("k"+to_string(k)+".txt",ios::out);
        plik_s[l].open("ks"+to_string(k)+".txt",ios::out);
        
        do{
            
            
            for(i=k;i<=(nx-k);i+=k)
                for(j=k;j<=(ny-k);j+=k)
                   v[i][j]=0.25*(v[i+k][j]+v[i-k][j]+v[i][j+k]+v[i][j-k]);
                    
            st=s;
            s=0.;
            for(i=0;i<=(nx-k);i+=k)
                for(j=0;j<=(ny-k);j+=k)
                {
                   s = s + 0.5 * k * k * delta * delta * (
        (v[i + k][j] - v[i][j] + v[i + k][j + k] - v[i][j + k]) / (2 * k * delta) * 
        (v[i + k][j] - v[i][j] + v[i + k][j + k] - v[i][j + k]) / (2 * k * delta) +
        (v[i][j + k] - v[i][j] + v[i + k][j + k] - v[i + k][j]) / (2 * k * delta) * 
        (v[i][j + k] - v[i][j] + v[i + k][j + k] - v[i + k][j]) / (2 * k * delta));
                 
                }
                it++;
              plik_s[l]<<it<<"\t"<<s<<endl;
            
        }while(fabs((s-st)/st)>=TOL);
        
        plik_s[l].close();

        //wpisujemy mape potencjalu
        for(i=0;i<(nx+1);i++)
            for(j=0;j<(ny+1);j++)
                plik[l]<<delta*i<<"\t"<<delta*j<<"\t"<<(v[i][j])<<endl;

        plik[l].close();
        
        //zageszczanie siatki
        if(k!=1)
        {
            for(i=0;i<=(nx-k);i+=k)
                for(j=0;j<=(ny-k);j+=k)
                {
                    v[i+k/2][j+k/2]=0.25*(v[i][j]+v[i+k][j]+v[i][j+k]+v[i+k][j+k]);
                    v[i+k][j+k/2]=0.5*(v[i+k][j]+v[i+k][j+k]);
                    v[i+k/2][j+k]=0.5*(v[i][j+k]+v[i+k][j+k]);
                    v[i+k/2][j]=0.5*(v[i][j]+v[i+k][j]);
                    v[i][j+k/2]=0.5*(v[i][j]+v[i][j+k]);
                }
        }   
    }


}