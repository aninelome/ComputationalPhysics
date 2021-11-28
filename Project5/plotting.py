import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa


fontsize = 13
ticksize = 13
legendsize = 13

P = pa.mat()
t_list = pa.mat()
x = pa.mat()
y = pa.mat()

P.load("P.bin")
x.load("x.bin")
y.load("y.bin")
t_list.load("t_list.bin")

N_t = len(t_list)

# Plot of the total probability as function of time:
for i in range(N_t):
    plt.plot(P[:,i],t_list)
plt.xlabel(" ")
plt.ylabel(" ")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title(" ",fontsize=fontsize)
plt.show()

## Colourmap plots that illustrate the time evolution
## of the 2D probability distribution:
#plt.contourf(x, y, P, 20)
#plt.plot()
#plt.xlabel(" ")
#plt.ylabel(" ")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title(" ",fontsize=fontsize)
#plt.show()

## Colourmap plots that show Re(u_ij) and Im(u_ij):
#plt.plot()
#plt.plot()
#plt.xlabel(" ")
#plt.ylabel(" ")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title(" ",fontsize=fontsize)
#plt.show()
#
## plot of the 1D probability distribution for detecting the particle
## along a strip near the right-hand wall
#plt.plot()
#plt.plot()
#plt.xlabel(" ")
#plt.ylabel(" ")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title(" ",fontsize=fontsize)
#plt.show()
#
## single-slit and triple-slit experiments:
#plt.plot()
#plt.plot()
#plt.xlabel(" ")
#plt.ylabel(" ")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title(" ",fontsize=fontsize)
#plt.show()
#
## 1D probability distributions along the right-hand wall:
#plt.plot()
#plt.plot()
#plt.xlabel(" ")
#plt.ylabel(" ")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title(" ",fontsize=fontsize)
#plt.show()
## Animations:
