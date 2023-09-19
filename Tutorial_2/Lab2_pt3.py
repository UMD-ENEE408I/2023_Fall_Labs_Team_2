from scipy.optimize import fsolve
from scipy.optimize import minimize_scalar
from scipy.fft import fft, fftfreq
import matplotlib.pyplot as plt
import numpy as np

#1
def eq(p):
    x,y = p
    return 3*x + y - 9, x+ 2*y -8
ans = fsolve(eq,(5,5))
print(ans)

#2
def eq2(p):
    x = p
    return pow(x,2) + 2*x
min = minimize_scalar(eq2)
print(min.fun)

#3
N = 600
T = 1/800
x = np.linspace(0,N*T,N)
y = np.sin(100*np.pi*x) + (1/2)* np.sin(160*np.pi*x)
yf = fft(y)
xf = fftfreq(N,T)[:N//2]

plt.plot(xf,2/N * np.abs(yf[0:N//2]))
plt.grid()
plt.show()



