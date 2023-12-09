import matplotlib.pyplot as plt
import numpy as np

import matplotlib.cm as cm

delta = 0.025
data = np.loadtxt("q1.txt")
x = data[:,0]
y = data[:,1]
z = data[:,3]

x = np.reshape(x, (len(np.unique(y)), -1))
y = np.reshape(y, (len(np.unique(y)), -1))
z = np.reshape(z, (len(np.unique(y)), -1))
# # y = np.arange(-2.0, 2.0, delta)

#X, Y = np.meshgrid(x, y)
# Z1 = np.exp(-X**2 - Y**2)
# Z2 = np.exp(-(X - 1)**2 - (Y - 1)**2)
# Z = (Z1 - Z2) * 2

fig, ax = plt.subplots()
levels=np.arange(-200, 300, 20)
CS = ax.contour(x,y,z,levels=levels,colors=['red','black','blue','#808080', '#A0A0A0', '#C0C0C0','#808080', '#A0A0A0', '#C0C0C0','blue'])

ax.clabel(CS, inline=True, fontsize=10)
ax.set_title('Simplest default with labels')
plt.savefig("plik.png")
