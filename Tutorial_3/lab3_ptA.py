#!/usr/bin/env python
# coding: utf-8

# # LAB 3 Tutorial

# In[1]:


import matplotlib.pyplot as plt
import numpy as np
import scipy


# ## Part A

# In[2]:


from scipy.io import wavfile
samplerate, data = wavfile.read('human_voice.wav')
print("sample rate: " + str(samplerate) + ", audio samples: " + str(len(data)))


# In[3]:


plt.figure(1)
plt.title("human_voice.wav")
# down sample to 8kHz from 48kHz or 1/6 the rate
plt.plot(data[3000:3600])
plt.ylabel("Magnitude")
plt.show()

down_sampled = data[0::6]
print("audio samples: " + str(len(down_sampled)))


# In[4]:


plt.figure(1)
plt.title("human_voice.wav Down Sampled")
# down sample to 8kHz from 48kHz or 1/6 the rate, for 3000:3600 / 6 = 500:600
plt.plot(down_sampled[500:600])
plt.ylabel("Magnitude")
plt.show()

