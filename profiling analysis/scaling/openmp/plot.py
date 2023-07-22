import numpy as np
import matplotlib.pyplot as plt

# get number of threads
data = np.loadtxt('elapsedtime_strongscaling.txt', dtype=str)
n_threads = np.zeros(len(data))
for i in range(len(data)):
    tmp = data[i,0]
    n_threads[i] = int(tmp[tmp.index('s')+1:tmp.index('/')])

# strong scaling
ts = data[:,1].astype(float)
plt.plot(n_threads, ts[n_threads==1]/ts, 'o', label='strong scaling')

# weak scaling
data = np.loadtxt('elapsedtime_weakscaling.txt', dtype=str)
ts = data[:,1].astype(float)
plt.plot(n_threads, n_threads*ts[n_threads==1]/ts, 'o', label='weak scaling')

plt.plot([1,32], [1,32], 'k--')

plt.text(1, 30, 'openmp', fontsize=15, horizontalalignment='left', verticalalignment='top')
plt.legend(loc=4, fontsize=15)
plt.xlabel('# of threads', fontsize=15)
plt.ylabel('speedup', fontsize=15)

plt.savefig('scaling_openmp.png')

