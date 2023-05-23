import csv
import matplotlib.pyplot as plt # for plotting
import numpy as np

t = [] # column 0
data1 = [] # column 1

with open('sigA.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data1.append(float(row[1])) # second column

#calculate sample rate
sample_rate = len(t)/t[-1]
print(sample_rate)

#FFT
Fs = sample_rate # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = data1 # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range
Y = np.fft.fft(y)/n # fft computing and normalization
Y = Y[range(int(n/2))]

#MAF
x = 500
maf = [] #new list
for i in range(len(t)-x):
    j = 0
    for h in range(x):
        j = (j + data1[i+h])
    j = j / x
    maf.append(j)

#IIR
A = .9
B = .1
iir = []
for i in range(len(t)):
    j = 0
    if i == 0:
        j = data1[i]
    else:
        j = A * iir[i-1] + B * data1[i]
    iir.append(j)

#Filtered FFT
Fs = sample_rate # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = iir # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq2 = k/T # two sides frequency range
frq2 = frq2[range(int(n/2))] # one side frequency range
Y2 = np.fft.fft(y)/n # fft computing and normalization
Y2 = Y2[range(int(n/2))]

#FIR
#sigA, cutoff freq of 10hz
fir = []
#paste h here from website: I ended up using the same for all signals
h = [
    -0.000000000000000001,
    0.000127579613445419,
    0.000538243550143906,
    0.001294658116032123,
    0.002482845649513765,
    0.004202322157352331,
    0.006551851651454681,
    0.009612489106623668,
    0.013430073927750511,
    0.017999556126845812,
    0.023253449134322375,
    0.029056307538842772,
    0.035206467177489292,
    0.041445437100763684,
    0.047474402645564739,
    0.052976403831180012,
    0.057642008946477953,
    0.061195807446116170,
    0.063420866509699705,
    0.064178459540761873,
    0.063420866509699705,
    0.061195807446116170,
    0.057642008946477974,
    0.052976403831180033,
    0.047474402645564753,
    0.041445437100763684,
    0.035206467177489278,
    0.029056307538842783,
    0.023253449134322389,
    0.017999556126845812,
    0.013430073927750521,
    0.009612489106623686,
    0.006551851651454687,
    0.004202322157352330,
    0.002482845649513761,
    0.001294658116032126,
    0.000538243550143905,
    0.000127579613445416,
    -0.000000000000000001,
]
for i in range(len(t)-len(h)):
    d = 0
    for j in range(len(h)):
        d = d + data1[i+j]*h[j]
    fir.append(d)

#FIR Filtered FFT
Fs = sample_rate # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = fir # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq3 = k/T # two sides frequency range
frq3 = frq3[range(int(n/2))] # one side frequency range
Y3 = np.fft.fft(y)/n # fft computing and normalization
Y3 = Y3[range(int(n/2))]

#plots

#for part 4
#fig, (ax1, ax2) = plt.subplots(2, 1)
#ax1.plot(t,y,'black')
#ax1.set_xlabel('Time')
#ax1.set_ylabel('Amplitude')
#ax2.loglog(frq,abs(Y),'b') # plotting the fft
#ax2.set_xlabel('Freq (Hz)')
#ax2.set_ylabel('|Y(freq)|')
#plt.show()

#for part 5
#fig, (ax1, ax2, ax3) = plt.subplots(3, 1)
#ax1.plot(t,y,'black')
#ax1.set_xlabel('Time')
#ax1.set_ylabel('Amplitude')
#ax2.loglog(frq,abs(Y),'b') # plotting the fft
#ax2.set_xlabel('Freq (Hz)')
#ax2.set_ylabel('|Y(freq)|')
#ax3.plot(t[0:(len(t)-x)],maf,'r')
#ax3.set_xlabel('Time')
#ax3.set_ylabel('Amplitude')
#ax3.set_title('x = 50')

#for part 6
#fig, (ax1, ax2) = plt.subplots(2, 1)
#ax1.plot(t, data1, 'black', t, iir, 'r')
#ax1.set_xlabel('Time')
#ax1.set_ylabel('Amplitude')
#ax2.set_title('A = .9, B = .1')
#ax2.loglog(frq,abs(Y),'b', frq2, abs(Y2), 'r') # plotting the fft
#ax2.set_xlabel('Freq (Hz)')
#ax2.set_ylabel('|Y(freq)|')
#plt.show()

#for part 7
fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(t, data1, 'black', t[0:(len(t)-len(h))], fir, 'r')
ax1.set_xlabel('Time')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq,abs(Y),'b', frq3, abs(Y3), 'r') # plotting the fft
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
ax2.set_title('Fl = 100hz, bl = 1200hz, #weights = 39, low-pass FIR')
plt.show()
