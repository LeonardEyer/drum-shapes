import matplotlib.pyplot as plt
import pdb
plt.ion()
from scipy.fftpack import fft
from scipy.io import wavfile # get the api
#fs, data = wavfile.read('/home/tobias/Downloads/Ensoniq-SQ-1-ClassicGuitar-C5.wav') # load the data
fs, data = wavfile.read('/home/tobias/Downloads/Alesis-Fusion-Nylon-String-Guitar-C4.wav') # load the data
a = data.T[0]  # this is a two channel soundtrack, I get the first track
# b = [(ele / 2 ** 8.) * 2 - 1 for ele in a]  # this is 8-bit track, b is now normalized on [-1,1)
c = fft(a)  # calculate fourier transform (complex numbers list)
d = len(c) // 2  # you only need half of the fft list (real signal symmetry)
plt.xlim(0,8000)
plt.plot(abs(c[:d - 1]), 'r')
pdb.set_trace()
print(c)
#plt.sho()
