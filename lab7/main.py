import matplotlib.pyplot as plt
import numpy as np

import matplotlib.cm as cm

#data = np.loadtxt("q1.txt")
indexi=0
indexj=0

data = np.loadtxt("q1.txt")
x = data[:,0]
y = data[:,1]
xx=[]
yy=[]
for i in range(len(x)):
    xx.append(x[i])
for j in range(len(y)):
    yy.append(y[j])
z = data[:,2]
X,Y=np.meshgrid(x,y)
# z = np.sqrt(X**2 + Y**2)
Z=[]
for i in range(len(x)):
    Z.append([])
    for j in range(len(y)):
        Z[i].append(0)
j=0
for i in range(len(x)):
    Z[i][j]=z[i]
    print(z[i])
    j+=1

# for i in range(200):
#     for j in range(90):
#         try:
#             indexi = xx.index(i*0.01)
#             indexj = yy.index(j*0.01)
#         except ValueError:
#             #Z[i][j]=-20
#             print("ERROR")
#         else:
#             print("OK")
#             Z[i][j]=z[indexj]
# # y = np.arange(-2.0, 2.0, delta)

#X, Y = np.meshgrid(x, y)
# Z1 = np.exp(-X**2 - Y**2)
# Z2 = np.exp(-(X - 1)**2 - (Y - 1)**2)
# Z = (Z1 - Z2) * 2

norm = cm.colors.Normalize(vmax=abs(z).max(), vmin=-abs(z).max())
cmap = cm.PRGn

levels=np.linspace(-55,-50,100)
CS = plt.contour(X,Y,Z,levels=levels)

plt.clabel(CS, inline=True, fontsize=10)
plt.colorbar(CS)
plt.title('Simplest default with labels')
plt.savefig("plik.png")