import numpy as np
import matplotlib.pyplot as plt

fig = plt.figure(figsize=(9,4.5))
fig.subplots_adjust(left=0.08, right=0.98)

# get number of cores and threads
data = np.loadtxt('elapsedtime_strongscaling.txt', dtype=str)
n_cores = np.zeros(len(data))
n_threads = np.zeros(len(data))
for i in range(len(data)):
    tmp = data[i,0]
    n_cores[i] = int(tmp[1:tmp.index('_')])
    n_threads[i] = int(tmp[tmp.index('s')+1:tmp.index('/')])

# strong scaling
ts = data[:,1].astype(float)

plt.subplot(121)
for n_thread in [1,2,4]:
    ii = n_threads == n_thread
    ts_ = ts[ii]
    t0 = ts_[n_cores[ii] == 1]
    plt.plot(n_cores[ii], t0/ts_, 'o', label='%d threads' % n_thread)

plt.plot([1,32], [1,32], 'k--')
plt.legend(fontsize=15, loc=4)
plt.xlabel('# of processes', fontsize=15)
plt.ylabel('speedup', fontsize=15)
plt.text(1, 30, 'hybrid\nstrong scaling', fontsize=15, horizontalalignment='left', verticalalignment='top')

# weak scaling
data = np.loadtxt('elapsedtime_weakscaling.txt', dtype=str)
ts = data[:,1].astype(float)

plt.subplot(122)
for n_thread in [1,2,4]:
    ii = n_threads == n_thread
    ts_ = ts[ii]
    t0 = ts_[n_cores[ii] == 1]
    plt.plot(n_cores[ii], n_cores[ii]*t0/ts_, 'o', label='%d threads' % n_thread)

plt.plot([1,32], [1,32], 'k--')
plt.legend(fontsize=15, loc=4)
plt.xlabel('# of processes', fontsize=15)
plt.ylabel('speedup', fontsize=15)
plt.text(1, 30, 'hybrid\nweak scaling', fontsize=15, horizontalalignment='left', verticalalignment='top')

plt.savefig('scaling_hybrid.png')

