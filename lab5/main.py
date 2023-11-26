import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colormaps

plt.figure()
   
plt.title("Proba")
data=np.loadtxt("k16.txt")

plt.tricontourf(data[:,0],data[:,1],data[:,2],cmap='magma')
plt.colorbar(ticks=np.linspace(min(data[:, 2]), max(data[:, 2]), 11))
plt.xlabel('x')
plt.ylabel('y')   
plt.savefig("Proba.png")
