import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pyarma as pa


fontsize = 36
ticksize = 36
legendsize = 36

P = pa.mat()
U_re = pa.mat()
U_im = pa.mat()

P_tot = pa.mat()
t_list = pa.mat()
x = pa.mat()
y = pa.mat()

P.load("P.bin")
P_tot.load("P_tot.bin")
x.load("x.bin")
y.load("y.bin")
t_list.load("t_list.bin")

N_t = len(t_list)
M = 201


diff_array = np.zeros_like(P_tot)
time_array = np.zeros_like(t_list)

for i in range(len(P_tot)):
    diff_array[i] = np.log10(abs(1-P_tot[i]))
    time_array[i] = t_list[i]

no_inf = np.logical_not(np.isinf(diff_array))
diff_array = diff_array[no_inf]
time_array = time_array[no_inf]
print(diff_array)
# Plot of the total probability as function of time:
fig, ax1 = plt.subplots()
l, b, h, w = .2, .2, .32, .33
ax2 = fig.add_axes([l, b, w, h])
for v,t in zip(diff_array,time_array):
    ax1.scatter(t, v)
ax1.set_xticks([0,0.002,0.004,0.006,0.008])
ax1.set_yticks([-15.5,-14.5,-13.5])
ax1.set_xticklabels([0,0.002,0.004,0.006,0.008], fontsize=fontsize)
ax1.set_yticklabels([-15.5,-14.5,-13.5], fontsize=fontsize)
ax1.set_xlabel("time", fontsize=fontsize)
#ax1.set_ylabel("probability", fontsize=fontsize)
#ax1.set_xticks()
#ax1.set_yticks()
#ax1.set_xticklabels(t_list,fontsize=fontsize)
#ax1.set_yticklabels(P_tot,fontsize=fontsize)
#ax2.set_xlabel("time", fontsize=fontsize)
ax2.plot(t_list, P_tot)
ax2.set_ylim(-1,2)
ax2.set_xticks([0,0.004,0.008])
ax2.set_yticks([-1,0,1,2])
ax2.set_xticklabels([0,0.004,0.008], fontsize=fontsize)
ax2.set_yticklabels([-1,0,1,2], fontsize=fontsize)
#ax2.set_ylabel("probability", fontsize=fontsize)
#plt.legend(prop={'size': 13})
#ax2.set_xticks(size=ticksize)
#ax2.set_yticks(size=ticksize)
plt.show()

# Colourmap plots that illustrate the time evolution
# of the 2D probability distribution:
times = [0, 40, 80]
P_mat = np.zeros((M-2,M-2))
for j in times:
    for i in range(M-2):
        P_mat[:,i] = P[(M-2)*i:(M-2)*(i+1)-1,j]
    X, Y = np.meshgrid(x,y)
    plt.contourf(X, Y, P_mat, 20)
    plt.plot()
    plt.title(f"Probability function at t = {j*0.000025}",fontsize=fontsize)
    plt.colorbar()
    plt.xlabel("x", fontsize=fontsize)
    plt.ylabel("y", fontsize=fontsize)
    plt.legend(prop={'size': 13})
    plt.xticks(size=ticksize)
    plt.yticks(size=ticksize)
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
