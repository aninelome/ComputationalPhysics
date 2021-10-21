from plotting import analytic_f
import matplotlib.pyplot as plt
import pyarma as pa
import numpy as np



fontsize = 10
ticksize = 10


#method = "RK4"
method = "ForwardEuler"



# Graph showing the size of the relative error for five different values for dt
dt = ["1", "2", "3", "4", "5"]
delta_max = np.zeros(5)
for value in dt:
    r = pa.cube()
    v = pa.cube()
    t = pa.mat()


    r.load(f"position_without_interaction_dt:10e-{value}.bin")
    v.load(f"velocity_without_interaction_dt:10e-{value}.bin")

    t.load(f"time_dt:10e-{value}.bin")

    r = np.array(r)
    v = np.array(v)
    t = np.array(t)

    r = r[:, :, 0]
    print(r.shape)
    #print(r[:5,:])
    #print(t[:5])


    x_analytic, y_analytic, z_analytic, time = analytic_f(dt=1/(pow(10,float(value)-1)))
    r_analytic = np.transpose([x_analytic, y_analytic, z_analytic])
    relative_error = np.sqrt((r[:,0] - r_analytic[:,0])**2 + (r[:,1] - r_analytic[:,1])**2 + (r[:,2] - r_analytic[:,2])**2)/np.sqrt(r_analytic[:,0]**2 + r_analytic[:,1]**2 + r_analytic[:,2]**2)
    print(r_analytic.shape)

    delta_max[int(value)-1] = np.max(r_analytic - r)

    plt.plot(time, relative_error, label=f"dt = 10e-{value}")

plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
if method == "RK4":
    plt.title(f"Relative error with different timesteps dt, with method: {method}", fontsize=12)
elif method == "ForwardEuler":
    plt.title(f"Relative error with different timesteps dt, with method: {method}", fontsize=12)
else:
    print("No method given")

plt.legend()
plt.show()

#Computation estimating the error convergence rate for forward Euler and RK4
print(delta_max)
sum = 0
for k in range(1,5):
    sum += (np.log10(delta_max[k]/delta_max[k-1]))/(np.log10(int(dt[k])/int(dt[k-1])))
r_err = (1/4)*sum

print(r_err)
