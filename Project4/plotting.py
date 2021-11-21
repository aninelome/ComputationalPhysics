import numpy as np
import matplotlib.pyplot as plt
import pyarma as pa
from scipy.interpolate import UnivariateSpline
from scipy.stats import linregress

fontsize = 13
ticksize = 13
legendsize = 13


# Problem 5
T_list = [1, 2.4]

for T in T_list:
    m_abs = pa.mat()
    N_c = pa.mat()

    m_abs.load(f"m_abs_vecT:{T}.bin")
    N_c.load(f"N_c_vecT:{T}.bin")

    m_abs_o = pa.mat()
    m_abs_o.load(f"m_abs_vecT:{T}_o.bin")

    plt.plot(N_c, m_abs)
    plt.plot(N_c, m_abs_o)
plt.xlabel("N_cycles")
plt.ylabel("<|m|>")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("",fontsize=fontsize)
plt.show()

for T in T_list:
    eps_exp = pa.mat()
    N_c = pa.mat()

    eps_exp.load(f"eps_exp_vecT:{T}.bin")
    N_c.load(f"N_c_vecT:{T}.bin")

    eps_exp_o = pa.mat()
    eps_exp_o.load(f"eps_exp_vecT:{T}_o.bin")


    plt.plot(N_c, eps_exp)
    plt.plot(N_c, eps_exp_o)
plt.xlabel("N_cycles")
plt.ylabel(f"$<\epsilon>$ [J]")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("",fontsize=fontsize)
plt.show()

# Problem 6
for T in T_list:
    eps.load(f"eps_vecT:{T}.bin")

    plt.hist(eps, 100, density=True)
plt.xlabel(f"$\epsilon$ [J]", size = fontsize)
plt.ylabel(f"$p$")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title(f"Normalized histogram of $\epsilon$ samples for T = {T} J/$k_B$",fontsize=fontsize)
plt.show()

#Problem 8
# Heat capacity as a function of temperature
# for different lattice sizes
C_v_list = []

L_list = [40, 60, 80, 100]
for L in L_list:
    C_v = pa.mat()
    T = pa.mat()

    C_v.load(f"C_v_vec{L}.bin");
    C_v_list.append(C_v)
    T.load("T_list.bin");

    plt.plot(T, C_v)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel(f"$C_v$")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Heat capacity as a function of temperature",fontsize=fontsize)
plt.show()

# The susceptibility as a function of temperature
# for different lattice sizes
for L in L_list:
    X = pa.mat()
    T = pa.mat()

    X.load(f"X_vec{L}.bin");
    T.load("T_list.bin");
    plt.plot(T, X)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel(f"$\chi$")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("The susceptibility as a function of temperature",fontsize=fontsize)
plt.show()

# Expectation value for energy per spin as a function of temperature
# for different lattice sizes
for L in L_list:
    eps_exp_temp = pa.mat()
    T = pa.mat()

    eps_exp_temp.load(f"eps_exp_temp{L}.bin");
    T.load("T_list.bin");
    plt.plot(T, eps_exp_temp)
plt.xlabel(f"T $[J/k_B]$")
plt.ylabel(f"$<\epsilon>$ [J]")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Expectation value for energy per spin as a function of temperature",fontsize=fontsize)
plt.show()

# Expectation value for the absolute value of the magnetization per spin,
# as a function of temperature for different lattice sizes
for L in L_list:
    m_abs_temp = pa.mat()
    T = pa.mat()

    m_abs_temp.load(f"m_abs_temp{L}.bin");
    T.load("T_list.bin");

    plt.plot(T, m_abs_temp)

plt.xlabel(f"T $[J/k_B]$")
plt.ylabel("<|m|>")
plt.legend(prop={'size': 13})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Expectation value for the absolute value of the magnetization per spin \n as a function of temperature",fontsize=fontsize)
plt.show()

# Problem 9
critical_temp = []
for C_v, L in zip(C_v_list, L_list):
    spl = UnivariateSpline(T, C_v, k=4, s=None) # Interpolating C_v against T
    spl.set_smoothing_factor(0.5)
    plt.plot(T, spl(T), label = f"L = {L}")
    critical_temp.append(spl.derivative().roots()) # Findig the maximum point of the interpolated C_v against T

plt.xlabel("T [$J/k_B$]", size = fontsize)
plt.ylabel("$C_v[k_B/J^2]$", size = fontsize)
plt.legend(prop={'size': fontsize})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Heat capacity as a function of temperature",fontsize=fontsize) #Interpolation
plt.show()

# Doing a linear regression for the critical temperature against lattice size
x = [100,80,60,40]
y = np.flip(critical_temp)

linreg = st.linregress([x,y]) # We can find the std of the intercept by printing linreg
a, b = linreg[0], linreg[1]
L = np.linspace(30,110,10000)

T_c = a*L + b

plt.plot(L, T_c, label = "Linear regression")
plt.plot(x, y, "yo", markersize = 10, label = "Data points")
plt.xlim(110, 30)
plt.xlabel("Lattice size, L", size = fontsize)
plt.ylabel("T [$J/k_B$]", size = fontsize)
plt.legend(prop={'size': fontsize})
plt.xticks(size=ticksize)
plt.yticks(size=ticksize)
plt.title("Linear regression of the critical temperature",fontsize=fontsize)
plt.show()
