#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pyplot as plt
import numpy as np
import scipy


# ## Part C

# ## 1) Plot the audio signal "Cafe_with_noise.wav"

# In[2]:


from scipy.io import wavfile
samplerate, data = wavfile.read('Cafe_with_noise.wav')
plt.figure(1)
plt.title("cafe with noise.wav")
plt.plot(data)
plt.show()


# ## 2) Analyze the signal in the frequency domain

# In[3]:


from scipy.fft import rfft, rfftfreq

# Number of samples in normalized_tone
N = len(data)

yf = rfft(data)
xf = rfftfreq(N, 1 / samplerate)

plt.figure(2)
plt.plot(np.abs(yf))
plt.title("Signal in frequency domain")
plt.show()


# ## 3) Low pass filter

# In[7]:


yf[17800: 18000] = 0
yf[17300: 17400] = 0
yf[18400: 18500] = 0
plt.figure(3)
plt.plot(np.abs(yf))
plt.title("Filtered signal in frequency domain")
plt.xlim(0, 300000)
plt.show()


# In[8]:


from scipy.fft import irfft
filtered_data = irfft(yf)
plt.figure(4)
plt.plot(filtered_data)
plt.title("Filtered Cafe_with_noise.wav")
plt.show()


# ### Export audio in a file called "filtered_cafe.wav"

# In[6]:


# Remember SAMPLE_RATE = 48000 Hz is our playback rate
filtered_data_normalized = np.int16((filtered_data / filtered_data.max()) * 32767)
wavfile.write("filtered_cafe.wav", samplerate, filtered_data_normalized)
