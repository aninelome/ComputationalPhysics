import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
from scipy.interpolate import UnivariateSpline
from scipy.stats import linregress

fontsize = 13
ticksize = 13
legendsize = 13


# Problem 6
eps_exp1 = pa.mat()
eps1 = pa.mat()
m_abs1 = pa.mat()
N_c1 = pa.mat()

eps_exp1.load("eps_exp_vec_T:1.bin")
m_abs1.load("m_abs_vec_T:1.bin")
N_c1.load("N_c_vec_T:1.bin")

eps1.load("eps_vec_T:1.bin")

eps_exp24 = pa.mat()
eps24 = pa.mat()
m_abs24 = pa.mat()
N_c24 = pa.mat()

eps_exp24.load("eps_exp_vec_T:24.bin")
m_abs24.load("m_abs_vec_T:24.bin")
N_c24.load("N_c_vec_T:24.bin")

eps24.load("eps_vec_T:24.bin")


eps_exp1_o = pa.mat()
eps1_o = pa.mat()
m_abs1_o = pa.mat()
N_c1_o = pa.mat()

eps_exp1_o.load("eps_exp_vec_T:1_o.bin")
m_abs1_o.load("m_abs_vec_T:1_o.bin")
N_c1_o.load("N_c_vec_T:1_o.bin")

eps1_o.load("eps_vec_T:1_o.bin")

eps_exp24_o = pa.mat()
eps24_o = pa.mat()
m_abs24_o = pa.mat()
N_c24_o = pa.mat()

eps_exp24_o.load("eps_exp_vec_T:24_o.bin")
m_abs24_o.load("m_abs_vec_T:24_o.bin")
N_c24_o.load("N_c_vec_T:24_o.bin")

eps24_o.load("eps_vec_T:24_o.bin")


plt.plot(N_c1, m_abs1, label="T=1, unordered")
plt.plot(N_c1, m_abs1_o, label="T=1, ordered")
plt.plot(N_c1, m_abs24, label="T=2.4, unordered")
plt.plot(N_c1, m_abs24_o, label="T=2.4, ordered")

plt.xlabel("N_cycles")
plt.ylabel("<|m|> [Enhet?]") #FIKS ENHET!!!
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("",fontsize=fontsize)
plt.show()

plt.plot(N_c1, eps_exp1, label="T=1, unordered")
plt.plot(N_c1, eps_exp1_o, label="T=1, ordered")
plt.plot(N_c1, eps_exp24, label="T=2.4, unordered")
plt.plot(N_c1, eps_exp24_o, label="T=2.4, ordered")

plt.xlabel("N_cycles")
plt.ylabel(f"$<\epsilon>$ [J]")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("",fontsize=fontsize)
plt.show()


plt.hist(eps1, 100, density=True)
plt.xlabel(f"$\epsilon$ [J]")
plt.ylabel(f"$p$")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("",fontsize=fontsize)
plt.show()

# Problem 8


# C_v_vec.save("C_v_vec"+to_string(L)+".bin");

#L_list = [40, 60, 80, 100]
#L = 80
#
#C_v = pa.mat()
#X = pa.mat()
#eps_exp_temp = pa.mat()
#m_abs_temp = pa.mat()
#T = pa.mat()
#
#C_v.load(f"C_v_vec{L}.bin");
#X.load(f"X_vec{L}.bin");
#eps_exp_temp.load(f"eps_exp_temp{L}.bin");
#m_abs_temp.load(f"m_abs_temp{L}.bin");
##T.load("T_list.bin");
#
## Heat capacity as a function of temperature
#T = np.linspace(2.1, 2.4, 10)
#plt.plot(T, C_v, "o")
#plt.xlabel(f"T $[J/k_B]$")
#plt.ylabel(f"$C_v$")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("Heat capacity as a function of temperature",fontsize=fontsize)
#plt.show()
#
## The susceptibility as a function of temperature
#plt.plot(T, X, "o")
#plt.xlabel(f"T $[J/k_B]$")
#plt.ylabel(f"$\chi$")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("The susceptibility as a function of temperature",fontsize=fontsize)
#plt.show()
#
## Expectation value for energy per spin as a function of temperature
#plt.plot(T, eps_exp_temp, "o")
#plt.xlabel(f"T $[J/k_B]$")
#plt.ylabel(f"$<\epsilon>$ [J]")
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("Expectation value for energy per spin as a function of temperature",fontsize=fontsize)
#plt.show()
#
## Expectation value for the absolute value of the magnetization per spin,
## as a function of temperature
#plt.plot(T, m_abs_temp, "o")
#plt.xlabel(f"T $[J/k_B]$")
#plt.ylabel("<|m|> [Enhet?]") #FIKS ENHET!!!
#plt.legend(prop={'size': 13})
#plt.xticks(size=ticksize)
#plt.yticks(size=ticksize)
#plt.title("Expectation value for the absolute value of the magnetization per spin \n as a function of temperature",fontsize=fontsize)
#plt.show()
#
## Problem 9
#
#spl = UnivariateSpline(T, C_v, k=4, s=None)
#spl.set_smoothing_factor(0.5)
#plt.plot(T, spl(T))
#plt.show()
#
#print(spl.derivative().roots())
#critical_temp = np.array([spl.derivative().roots()]) # Findig the maximum point of the interpolated C_v against T
#test = np.array([2.35, 2.3, 2.29, 2.28])
#
#x = [100,80,60,40]
##y = np.flip(critical_temp)
#y = np.flip(test)
#
#
#linreg = linregress([x,y])
#
#fig, ax = plt.subplots()
#ax.plot(x,y, 'yo')
#ax.set_xlim(110, 30)
#ax.set_ylim(2.25, 2.37)
#
#ax.plot(linreg)
#
##plt.show()
#
