import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import colormaps
k=[16,8,4,2,1]
cmap = matplotlib.cm.jet
plt.figure(figsize=(12, 7))


plt.subplot(2, 3, 6)
plt.title(" S(it) ")
for i in k:
    data=np.loadtxt(f"ks{i}.txt")
    plt.plot(data[:,0],data[:,1],label=f"k={i}")
plt.grid()
plt.xlabel('it')
plt.ylabel('S')  
plt.legend()

for i in range(len(k)):
    plt.subplot(2, 3, i+1) 
    a=k[i]
    plt.title(f"Mapa potencjału dla k ={a}")
    data=np.loadtxt(f"k{a}.txt")  

    plt.tricontourf(data[:,0],data[:,1],data[:,2],levels=np.linspace(np.min(data[:, 2]), np.max(data[:, 2]), 999),
                       cmap='rainbow_r')
    plt.colorbar(ticks=np.linspace(min(data[:, 2]), max(data[:, 2]),5))
    plt.tight_layout() 
    plt.xlabel('x')
    plt.ylabel('y')   
   
plt.tight_layout() 
plt.savefig("lab5.png")
