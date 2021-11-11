import numpy as np
import matplotlib.pyplot as plt 
import pyarma as pa

eps = pa.mat()
m_abs = pa.mat()
N_c = pa.mat()

eps.load("eps_vec.bin")
m_abs.load("m_abs_vec.bin")
N_c.load("N_c_vec.bin")

plt.plot(N_c, m_abs)
plt.xlabel("N_cycles")
plt.ylabel("|m| [Enhet?]") #FIKS ENHET!!!
plt.show()

plt.plot(N_c, eps)
plt.xlabel("N_cycles")
plt.ylabel(f"$\epsilon$ [J]")
plt.show()