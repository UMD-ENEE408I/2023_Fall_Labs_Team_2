import matplotlib.pyplot as plt
import numpy as np
import math

#1,2
x = np.arange(0,2*np.pi,0.1)
y = np.sin(x)
plt.plot(x,y)
plt.xlabel("rads")
plt.ylabel("amplitude")
plt.title("Sin graph")
plt.show()

plt.figure()
#3
ax = plt.axes(projection = '3d')
x = np.linspace(-5,5,1000)
y = np.linspace(-5,5,1000)
x,y = np.meshgrid(x,y)
z = np.sin(np.power((np.power(x,2) + np.power(y,2)),1/2))
ax.plot_surface(x,y,z)
plt.show()