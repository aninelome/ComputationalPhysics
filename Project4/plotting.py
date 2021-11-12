import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa

fontsize = 13
ticksize = 13
legendsize = 13

# Problem 6
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
#plt.ylabel("<|m|> [Enhet?]") #FIKS ENHET!!!
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("",fontsize=fontsize)
#plt.show()
#
#plt.plot(N_c, eps_exp)
#plt.xlabel("N_cycles")
#plt.ylabel(f"$<\epsilon>$ [J]")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("",fontsize=fontsize)
#plt.show()
#
#
#plt.hist(eps, 100, density=True)
#plt.xlabel(f"$\epsilon$ [J]")
#plt.ylabel(f"$p$")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("",fontsize=fontsize)
#plt.show()
#
# Problem 8
C_v = pa.mat()
X = pa.mat()
eps_exp_temp = pa.mat()
m_abs_temp = pa.mat()
T = pa.mat()

C_v.load("C_v_vec.bin");
X.load("X_vec.bin");
eps_exp_temp.load("eps_exp_temp.bin");
m_abs_temp.load("m_abs_temp.bin");
T.load("T_list.bin");

# Heat capacity as a function of temperature
plt.plot(T, C_v)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel(f"$C_v$")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Heat capacity as a function of temperature",fontsize=fontsize)
plt.show()

# The susceptibility as a function of temperature
plt.plot(T, X)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel(f"$\chi$")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("The susceptibility as a function of temperature",fontsize=fontsize)
plt.show()

# Expectation value for energy per spin as a function of temperature
plt.plot(T, eps_exp_temp)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel(f"$<\epsilon>$ [J]")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Expectation value for energy per spin as a function of temperature",fontsize=fontsize)
plt.show()

# Expectation value for the absolute value of the magnetization per spin,
# as a function of temperature
plt.plot(T, m_abs_temp)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel("<|m|> [Enhet?]") #FIKS ENHET!!!
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Expectation value for the absolute value of the magnetization per spin \n as a function of temperature",fontsize=fontsize)
plt.show()
