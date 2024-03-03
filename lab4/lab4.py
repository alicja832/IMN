import numpy as np
import matplotlib.pyplot as plt

w=['$\omega_L = 1.0$','$\omega_L = 1.4$','$\omega_L = 1.8$','$\omega_L = 1.9$']

files=["lok_1.000000.txt","lok_1.400000.txt","lok_1.800000.txt","lok_1.900000.txt"]

colors=['r','b','m','g']


plt.figure()
plt.title("Relaksacja lokalna")
for i in range (len(files)):
    file=files[i]
    data = np.loadtxt(file)
    x = data[:, 0][1:]
    y= data[:, 1][1:]
    plt.plot(x,y,colors[i]+'-',label=w[i]+" "+str(len(y)))
         
plt.legend()
plt.xscale('log')
plt.xlabel('nr iteracji')
plt.ylabel("S")   
plt.savefig("zad2.png")   
