import board
import digitalio
from ulab import numpy as np
import time

print("Running...")

a = np.zeros(1024)
b = np.zeros(1024)
c = np.zeros(1024)
d = np.zeros(1024)
i = 0

for i in range(1024):
    #create sin waves of different frequency
    a[i] = np.sin(i*.5)
    b[i] = np.sin(i*.25)
    c[i] = np.sin(i*.1)
    #create combined waves
    d[i] = a[i] + b[i] + c[i]

#create FFT, code taken from DSP HW
#ulab FFT, sends back 2 numbers, coefficients of real and complex

r, j = np.fft.fft(d)

for i in range(1024): #print FFT for plotting
    print((r[i],))
    time.sleep(.01)
