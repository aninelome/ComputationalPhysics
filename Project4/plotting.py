import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa

eps_exp = pa.mat()
eps = pa.mat()
m_abs = pa.mat()
N_c = pa.mat()

eps_exp.load("eps_exp_vec.bin")
m_abs.load("m_abs_vec.bin")
N_c.load("N_c_vec.bin")

eps.load("eps_vec.bin")

#plt.plot(N_c, m_abs)
#plt.xlabel("N_cycles")
#plt.ylabel("|m| [Enhet?]") #FIKS ENHET!!!
#plt.show()
#
#plt.plot(N_c, eps_exp)
#plt.xlabel("N_cycles")
#plt.ylabel(f"$<\epsilon>$ [J]")
#plt.show()

#fig, axs = plt.figure()
#axs.yaxis.set_major_formatter(PercentFormatter(xmax=1))

#plt.hist(eps, 100, density=True)
#plt.xlabel(f"$\epsilon$ [J]")
#plt.ylabel(f"$p$")
counts, bins, p=np.histogram(eps, density=True)
plt.hist(bins[:-1], bins, weights=counts)
plt.show()
