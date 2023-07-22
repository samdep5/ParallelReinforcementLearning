Hybrid Time measurements: output is in the form of 
Total reward/ total time    Percentage of corect actions/ total time    time(in seconds)

We ran trials for the scripts that outputted to a file titled "hybrid.txt"
The job is in hybridjob.sh.

OpenMP Time measurements: output is in the form of
Total reward/total time     Percetage of correct actions/total time     time(in seconds)
to a file titled "openmp.txt"
The job for the first set of numbers is openmpjob.sh. The two end values belong to the first two runs of openmplarger.sh

Note: if run mutliple times, the new results will be appended on to the txt files if they allready exist with results in them.

The openmp and mpi must first be compiled with the same make command as the originals. You can then submit the jobs with sbatch. Then, the data was plotted in graphsynchrate.py with matplotlib.