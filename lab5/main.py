import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import colormaps
k=[16,8,4,2,1]
cmap = matplotlib.cm.jet
plt.figure(figsize=(12, 7))


plt.subplot(2, 3, 6)
plt.title("S(it)")
for i in k:
    data=np.loadtxt(f"ks{i}.txt")
    plt.plot(data[:,0],data[:,1],label=f"k={i}")
it=data[:,0][len(data[:,0])-1]
plt.grid()
plt.xlabel('it')
plt.ylabel('S')
plt.text(100,4.8,f"Liczba iteracji:{it}")  
plt.legend()

for i in range(len(k)):
    plt.subplot(2, 3, i+1) 
    a=k[i]
    pkt=[]
    z=[]
    x=0
    #plt.figure()
    plt.title(f"Mapa potencjału dla k ={a}")
    data=np.loadtxt(f"k{a}.txt")
   
    pkt=[]
    for j in range (0,129):
        pkt.append([])
        for l in range (0,129):
            pkt[j].append(data[:,2][x])
            x+=1 
    print(len(pkt[0]))
    for j in range (0,129):
        for l in range (0,129):  
            if j==128 or l==128:
                z.append(pkt[j][l])  
            else:  
                z.append((pkt[(j//a)*a][(l//a)*a]+pkt[(j//a)*a+a][(l//a)*a+a])/2) 
                 
       
    plt.tricontourf(data[:,0],data[:,1],z,levels=np.linspace(np.min(data[:, 2]), np.max(data[:, 2]), 999),
                       cmap='rainbow_r')
    plt.colorbar(ticks=np.linspace(min(data[:, 2]), max(data[:, 2]),5))
    plt.tight_layout() 
    plt.xlabel('x')
    plt.ylabel('y')   
    
plt.tight_layout() 

plt.savefig("lab5.png")
