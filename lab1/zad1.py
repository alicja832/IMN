import numpy as np
import matplotlib.pyplot as plt


t=["0.01","0.10","1."]
zad=["","1.2:","1.3:"]
zera=["","","00"]
files=[[],[],[]]
colors=["b","r","g"]
titles=["Metoda Eulera","Metoda RK2","Metoda RK4"]
kl=0
for i in zad:
    for j in range(len(t)):
        files[kl].append("wynik"+i+t[j]+zera[j]+"0000.txt")
    kl+=1

for kl in range(3):
    fig=plt.figure(facecolor='white')
    plt.title(titles[kl]+" -rozwiązanie")
    for i in range (len(files[kl])):

        data = np.loadtxt(files[kl][i])
       
        x = data[:, 0]
        if(i==0):
            y_an = data[:, 2]
            plt.plot(x, y_an, 'k-', lw=2, label='analityczne')

        
        y = data[:, 1]
        plt.plot(x, y, colors[i]+"o", label='dt='+t[i])


    l1 = plt.legend()

    plt.xlabel('t')
    plt.ylabel('y(t)')

    plt.savefig("zad"+str(kl+1)+".png")

    fig=plt.figure(facecolor='white')
    plt.title(titles[kl]+" -błąd globalny")
    for i in range(len(files[kl])):

        data = np.loadtxt(files[kl][i])

        x = data[:, 0]
        y = data[:, 3]

        plt.plot(x, y, colors[i]+"-", label='dt='+t[i])

    
    plt.xlabel('t')
    plt.ylabel('ynum(t)-ydok(t)')

   
    if kl==1 or kl==2:
        x1, x2, y1, y2 = 0, 5, 0., 0.0008
        axins = plt.axes([0.55, 0.55, 0.3, 0.3])
        if kl==2:
           y2=4*1e-7
        for i in range(len(files[kl])):

            data = np.loadtxt(files[kl][i])

            x = data[:, 0]
            y = data[:, 3]
            axins.plot(x, y, colors[i]+"-")

        axins.set_xlim(x1, x2)
        axins.set_ylim(y1, y2)


            # Ustawienie granic okna z przybliżeniem
    else:
         l1 = plt.legend()

    plt.savefig("zad"+str(kl+1)+"a.png")

