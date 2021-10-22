from plotting import analytic_f
import matplotlib.pyplot as plt
import pyarma as pa
import numpy as np
import math



fontsize = 10
ticksize = 12

# In this program we need to do some changes when we switch from RK4 to ForwardEuler
# First, choose method here by commenting out the one we do not want:
#method = "RK4"
method = "ForwardEuler"


# Graph showing the size of the relative error for five different values for dt
#dt_list = ["2", "3", "4", "5", "6"]    #Use this list for RK4
dt_list = ["8", "9", "10", "11", "12"]  #Use this list for Forward Euler
delta_max = np.zeros(5)
for value in dt_list:
    dt = 1/(pow(2,float(value)))
    r = pa.cube()
    v = pa.cube()
    t = pa.mat()


    r.load(f"position_without_interaction_dt:2**-{value}.bin")
    v.load(f"velocity_without_interaction_dt:2**-{value}.bin")

    t.load(f"time_dt:2**-{value}.bin")

    r = np.array(r)
    v = np.array(v)
    t = np.array(t)

    r = r[:, :, 0]

    x_analytic, y_analytic, z_analytic, time = analytic_f(dt=dt)
    r_analytic = np.transpose([x_analytic, y_analytic, z_analytic])

    relative_error = np.linalg.norm(r - r_analytic, axis=1)/np.linalg.norm(r_analytic,axis=1)

    # NB: Here we need to subtract the first number in dt_list, so it depends on the method we use (RK4/FE):
    delta_max[int(value)-8] = np.max(np.abs(r_analytic - r))

    plt.plot(time, relative_error, label=f"h = {dt}")


if method == "RK4":
    plt.title(f"Relative error with different timesteps h, with method: {method}", fontsize=12)
elif method == "ForwardEuler":
    plt.title(f"Relative error with different timesteps h, with method: {method}", fontsize=12)
else:
    print("No method given")

plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.xlabel(f"$t\ [\mu s]$", fontsize=12)
plt.ylabel("Relative error", fontsize=12)
plt.legend(prop={'size': 12})
plt.show()

#Computation estimating the error convergence rate for forward Euler and RK4
dt_list = np.array([float(val) for val in dt_list])
dt_val_list = np.array(1/(pow(2,dt_list)))

sum = 0
for k in range(1,5):
    sum += (np.log10(delta_max[k]/delta_max[k-1]))/(np.log10(float(dt_val_list[k])/float(dt_val_list[k-1])))
r_err = (1/4)*sum

plt.plot(np.log10(dt_val_list), np.log10(delta_max))
plt.plot(np.log10(dt_val_list), np.log10(delta_max), "ro")
plt.title(f"{method}")
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.xlabel(f"$log(h)$", fontsize=12)
plt.ylabel("$log(\Delta_{max})$", fontsize=12)
plt.show()

# Write to file the values we get for dt, delta_max and convergence rate
outfile = open(f"error_{method}.txt", "w")
outfile.write(f"{method}: dt_val_list: {dt_val_list}\n")
outfile.write(f"{method}: delta_max: {delta_max}\n")
outfile.write(f"{method}: convergence rate: {r_err}\n")
outfile.close()
