import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import colormaps
k=[50,100,200]
cmap = matplotlib.cm.jet
plt.figure(figsize=(12, 7))

for i in range(len(k)):
    plt.subplot(2, 3, i+1) 
    a=k[i]
    pkt=[]
    x=0
    #plt.figure()
    plt.title(f"nx=ny={k[i]}"+r'$\epsilon$'+"=1")
    data=np.loadtxt(f"{k[i]}.txt")
       
    plt.tricontourf(data[:,0],data[:,1],data[:,2],levels=np.linspace(np.min(data[:, 2]), np.max(data[:, 2]), 999),
                       cmap='bwr')
    plt.colorbar(ticks=np.linspace(min(data[:, 2]), max(data[:, 2]),5),label="V")
    plt.tight_layout() 
    plt.xlabel('x')
    plt.ylabel('y')   
    
plt.tight_layout() 

plt.savefig("lab6.png")