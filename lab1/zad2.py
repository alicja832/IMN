import numpy as np
import matplotlib.pyplot as plt

w=["0.5 w_0","0.8 w_0","1.0 w_0","1.2 w_0"]
wynik=["50","80","100","120"]
files=[[],[]]

szukane=["Q","I"]
colors=['b','r','g','c']
n=0

for i in range (len(files)):
    for j in wynik:
        files[i].append("wynik"+szukane[i]+j+".txt")

for i in files:
    z=0
    plt.figure()
    plt.title("Metoda RK4, "+szukane[n]+"(t)")
    for j in i:
       data = np.loadtxt(j)
       x = data[:, 0]
       y= data[:, 1]
       plt.plot(x,y,colors[z]+'-',label=w[z])
       z+=1
    plt.legend()
    plt.xlabel('t')
    plt.ylabel(str(szukane[n])+"(t)")   
    plt.savefig("zad4"+szukane[n]+".png")
    n+=1