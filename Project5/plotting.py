import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa


fontsize = 13
ticksize = 13
legendsize = 13

t_list = pa.mat()
x = pa.mat()
y = pa.mat()



x.load("x.bin")
y.load("y.bin")
t_list.load("t_list.bin")

N_t = len(t_list)

P = []
for i in range(N_t):
    p = pa.mat()
    print(f"p{i}.bin")
    p.load(f"p{i}.bin")
    print(p)
    P.append(np.array(p))

X = np.array(x)
print("X ", X)
#print(x, y)

print(P)  # ALLE ELEMENTENE FÅR SIN EGEN ARRAY????

P_mat = np.zeros((N_t, len(P[0])))
for i in range(N_t):
    P_mat[i,:] = P[i][:]



## Plot of the total probability as function of time:
#plt.plot()
#plt.plot()
#plt.xlabel(" ")
#plt.ylabel(" ")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title(" ",fontsize=fontsize)
#plt.show()

# Colourmap plots that illustrate the time evolution
# of the 2D probability distribution:
plt.contourf(x, y, P_mat, 20)
#plt.plot()
plt.xlabel(" ")
plt.ylabel(" ")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title(" ",fontsize=fontsize)
plt.show()

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
