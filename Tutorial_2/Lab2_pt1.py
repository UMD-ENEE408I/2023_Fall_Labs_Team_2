import numpy as np
from numpy import linalg as LA

#1
nums = np.array([1,2,3,4])
#2
zeros = np.zeros((4,3))
ones = np.zeros((3,4))
#3
ary1 = np.array([[1,2,3], [1,2,3]])
ary2 = np.array([[1,2,3,4], [1,2,3,4], [1,2,3,4]])
ary3 = np.matmul(ary1,ary2)
print(ary3)
#4
ary4 = np.array([[3,1],[1,2]])
eigenvals, eigenvectors = LA.eig(ary4)
print(ary4)
print(eigenvals)
print(eigenvectors)

