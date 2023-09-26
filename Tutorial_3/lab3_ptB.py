from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np
import math

samplerate_M1, data_M1 = wavfile.read('lab_env/M1.wav')
samplerate_M2, data_M2 = wavfile.read('lab_env/M2.wav')
samplerate_M3, data_M3 = wavfile.read('lab_env/M3.wav')

data_M1 = np.array(data_M1, dtype= "int64")
data_M2 = np.array(data_M2, dtype= "int64")
data_M3 = np.array(data_M3, dtype= "int64")


rms_wav1 = np.sqrt(np.mean(data_M1**2))
rms_wav2 = np.sqrt(np.mean(data_M2**2))
rms_wav3 = np.sqrt(np.mean(data_M3**2))

print("rms 1:" + str(rms_wav1))
print("rms 2:" + str(rms_wav2))
print("rms 3:" + str(rms_wav3))

rxy = np.zeros(len(data_M2))
data_m4 = np.hstack((np.zeros(8000),data_M1))
data_m5 = np.hstack((data_M1,(np.zeros(8000))))

# Pre-allocate correlation array
corr1 = (len(data_m4) - len(data_M2) + 1) * [0]
corr2 = (len(data_m4) - len(data_M2) + 1) * [0]

print(len(corr1))
print(len(data_M2))
print(len(data_m4))



# Go through lag components one-by-one
for l in range(len(corr1)):
    corr1[l] = sum([data_m4[i+l] * data_M2[i] for i in range(len(data_M2))])

for l in range(len(corr2)):
    corr2[l] = sum([data_m5[i+l] * data_M2[i] for i in range(len(data_M2))])

output = np.hstack((corr1,corr2))

plt.plot(output)
plt.show()