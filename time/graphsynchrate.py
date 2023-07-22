import matplotlib.pyplot as plt
#This was used to graph the results for sych rate

x = [1,2,4,8,16,32, 64, 128, 256, 512, 1024, 2048]
# PSA= [8.1222e-10	,9.6463e-10	,1.02594e-09	,1.02575e-09	,8.86798e-10	,1.0686e-09	,9.57906e-10	,8.44853e-10	,1.0548e-09	,1.06675e-09	,1.04208e-09	,1.05201e-9]

x = [1,2,4,8,16,32,64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384]
xm = [1,2,4,8,16,32,64, 128, 256, 512, 1024, 2048, 4096]
OMP_R = [
221650 ,
115993 ,
58344.2,
31413.3,
15857.1,
8080.02,
4080.09,
2034.88,
1003.49,
521.149,
255.885,
135.268,
78.6547,
45.7573,
30.9941,
]

OMP_T = [0.0187657,
0.0188793,
0.0124082	,
0.0189969	,
0.0188804	,
0.0190502	,
0.0188438	,
0.0188274	,
0.0181338	,
0.000501232	,
0.0185449	,
0.0178181	,
0.0155895	,
0.0158627	,
0.0188236	,
]


MPI_R = [
    104.82,
112.521,
112.284,
112.745,
94.0451,
85.2904,
93.8055,
99.7932,
102.352,
96.3672,
89.1973,
61.9444,
28.8748
]

MPI_T = [
0.0649781,
0.0659141,
0.0657641,
0.0670824,
0.0592282,
0.0497907,
0.0567123,
0.0615275,
0.045739,
0.0530138,
0.0580999,
0.058379,
0.0667299,
]

plt.xscale("log")
plt.plot(x, OMP_R, "-*")  
plt.xlabel('Iterations per Episode (log-based scale)')
plt.ylabel('Total Reward / Total Time [Reward/S]')
plt.title("OpenMp Sync Rate with 131,072 Actions")
plt.show()

plt.xscale("log")
plt.plot(x, OMP_T, "-*")  
plt.xlabel('Iterations per Episode (log-based scale)')
plt.ylabel('Percentage of Correct Actions / Total Time [Reward/S]')
plt.title("OpenMp Correctness Rate with 131,072 Actions")
plt.show()

plt.xscale("log")
plt.plot(xm, MPI_R, "r-*")  
plt.xlabel('Iterations per Episode (log-based scale)')
plt.ylabel('Total Reward / Total Time [Reward/S]')
plt.title("Hybrid Sync Rate with 131,072 Actions")
plt.show()

plt.xscale("log")
plt.plot(xm, MPI_T, "r-*")  
plt.xlabel('Iterations per Episode (log-based scale)')
plt.ylabel('Percentage of Correct Actions / Total Time [Reward/S]')
plt.title("Hybrid Correctness Rate with 131,072 Actions")
plt.show()