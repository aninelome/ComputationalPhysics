from plotting import analytic_f
import matplotlib.pyplot as plt
import pyarma as pa
import numpy as np



fontsize = 10
ticksize = 10

#interaction = True
interaction = False


# Graph showing the size of the relative error for five different values for dt
dt = ["0.500000", "0.100000", "0.010000", "0.001000", "0.000100"]
for value in dt:
    r = pa.cube()
    v = pa.cube()
    t = pa.mat()

    if interaction:
        interaction_label = "with interaction"
        r.load(f"position_with_interaction_{value}.bin")
        v.load(f"velocity_with_interaction_{value}.bin")
    else:
        interaction_label = "without interaction"
        r.load(f"position_without_interaction_{value}.bin")
        v.load(f"velocity_without_interaction_{value}.bin")

    t.load("time.bin")

    r = np.array(r)
    v = np.array(v)
    t = np.array(t)

    r = r[:, :, 0]

    x_analytic, y_analytic, z_analytic, time = analytic_f(dt=float(value))
    r_analytic = np.transpose([x_analytic, y_analytic, z_analytic])
    relative_error = np.sqrt((r_analytic[:,0] - r[:,0])**2 + (r_analytic[:,1] - r[:,1])**2 + (r_analytic[:,2] - r[:,2])**2)/np.sqrt(r_analytic[:,0]**2 + r_analytic[:,1]**2 + r_analytic[:,2]**2)

    print(relative_error[:5])
    plt.plot(time, relative_error, label=f"dt = {value}")

plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.legend()
plt.show()

# Computation estimating the error convergence rate for forward Euler and RK4
#delta_max = np.max(np.abs(?))
#sum = 0
#for k in range(2,6):
#    sum += (np.log10(delta_max[k]/delta_max[k-1]))/(np.log10(dt[k]/dt[k-1])
#    r_err = (1/4)*sum
