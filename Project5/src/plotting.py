import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import pyarma as pa
import seaborn as sns


fontsize = 36
ticksize = 36
legendsize = 36

# Loading data from c++
P = pa.mat()
U_re = pa.mat()
U_im = pa.mat()
P_tot = pa.mat()
t_list = pa.mat()
x = pa.mat()
y = pa.mat()

P.load("P.bin")
U_re.load("U_re.bin")
U_im.load("U_im.bin")
P_tot.load("P_tot.bin")
x.load("x.bin")
y.load("y.bin")
t_list.load("t_list.bin")


N_t = len(t_list)   # number of time steps
M = 201             # number of points along the x- and y-axis, including the boundary points


diff_array = np.zeros_like(P_tot)
time_array = np.zeros_like(t_list)

for i in range(len(P_tot)):
    diff_array[i] = np.log10(abs(1-P_tot[i])) # log of the absolute error of the total probability
    time_array[i] = t_list[i]

no_inf = np.logical_not(np.isinf(diff_array)) # dealing with some "inf" values due to really small error
diff_array = diff_array[no_inf]
time_array = time_array[no_inf]

# Plot of the absolute error of the total probability as function of time,
# with a small plot of the total probability inside:
fig, ax1 = plt.subplots()
l, b, h, w = .5, .25, .32, .33
ax2 = fig.add_axes([l, b, w, h])
for v,t in zip(diff_array,time_array):
    ax1.scatter(t, v, color="orchid")
ax1.set_xticks([0,0.002,0.004,0.006,0.008])
ax1.set_yticks([-15.5,-14.5,-13.5])
ax1.set_xticklabels([0,0.002,0.004,0.006,0.008], fontsize=fontsize)
ax1.set_yticklabels([-15.5,-14.5,-13.5], fontsize=fontsize)
ax1.set_xlabel("time", fontsize=fontsize)
ax1.set_ylabel("error", fontsize=fontsize)
ax2.plot(t_list, P_tot, color = "indigo")
ax2.set_ylim(-1,2)
ax2.set_xticks([0,0.004,0.008])
ax2.set_yticks([-1,0,1,2])
ax2.set_xticklabels([0,0.004,0.008], fontsize=25)
ax2.set_yticklabels([-1,0,1,2], fontsize=25)
ax2.set_ylabel("probability", fontsize=25)
plt.show()

# Colourmap plots that illustrate the time evolution
# of the 2D probability distribution with a double slit
times = [0, 39, 79]
time_title = [0, 0.001, 0.002]
P_mat = np.zeros((M-2,M-2))
U_re_mat = np.zeros((M-2,M-2))
U_im_mat = np.zeros((M-2,M-2))
for j in range(len(times)):
    for i in range(M-2):
        P_mat[:, i] = P[(M-2)*i:(M-2)*(i+1)-1,times[j]]
        U_re_mat[:, i] = U_re[(M-2)*i:(M-2)*(i+1)-1,times[j]]
        U_im_mat[:, i] = U_im[(M-2)*i:(M-2)*(i+1)-1,times[j]]


    X, Y = np.meshgrid(x,y)
    plt.contourf(X, Y, P_mat.T, 20)
    plt.title(f"Probability function at t = {time_title[j]} \n",fontsize=fontsize)
    cb = plt.colorbar()
    cb.set_label(label='Probability', size=fontsize)
    cb.ax.tick_params(labelsize=fontsize)
    plt.xlabel("x", fontsize=fontsize)
    plt.ylabel("y", fontsize=fontsize)
    plt.xticks([0.2,0.4,0.6,0.8,1],size=ticksize)
    plt.yticks([0,0.2,0.4,0.6,0.8],size=ticksize)
    plt.show()
    # Colourmap plots that show Re(u_ij) and Im(u_ij):
    plt.contourf(X, Y, U_re_mat.T, 20)
    plt.title(f"Real part of the wave function at t = {time_title[j]} \n",fontsize=fontsize)
    cb = plt.colorbar()
    cb.set_label(label='Real part', size=fontsize)
    cb.ax.tick_params(labelsize=fontsize)
    plt.xlabel("x", fontsize=fontsize)
    plt.ylabel("y", fontsize=fontsize)
    plt.xticks([0.2,0.4,0.6,0.8,1],size=ticksize)
    plt.yticks([0,0.2,0.4,0.6,0.8],size=ticksize)
    plt.show()
    plt.contourf(X, Y, U_im_mat.T, 20)
    plt.title(f"Imaginary part of the wave function at t = {time_title[j]} \n",fontsize=fontsize)
    cb = plt.colorbar()
    cb.set_label(label='Imaginary part', size=fontsize)
    cb.ax.tick_params(labelsize=fontsize)
    plt.xlabel("x", fontsize=fontsize)
    plt.ylabel("y", fontsize=fontsize)
    plt.xticks([0.2,0.4,0.6,0.8,1],size=ticksize)
    plt.yticks([0,0.2,0.4,0.6,0.8],size=ticksize)
    plt.show()


# Plot of the 1D probability distribution for the particle
# along a strip near the right-hand wall ( at x = 0.8)
P_mat = np.zeros((M-2,M-2))
for i in range(M-2):
    P_mat[:,i] = P[(M-2)*i:(M-2)*(i+1)-1,79]
Px = P_mat.T[:,160]
Px = Px/np.sum(Px)
plt.plot(y,Px)
plt.xlabel("y", fontsize=fontsize)
plt.ylabel("probability", fontsize=fontsize)
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
# Double slit:
plt.title("Probability function at $x=0.8$ and $t=0.002$ \n Double slit",fontsize=fontsize)
# Single slit:
#plt.title("Probability function at $x=0.8$ and $t=0.002$ \n Single slit",fontsize=fontsize)
# Triple slit:
#plt.title("Probability function at $x=0.8$ and $t=0.002$ \n Triple slit",fontsize=fontsize)
plt.show()
