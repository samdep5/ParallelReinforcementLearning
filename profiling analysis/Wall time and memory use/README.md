# Files

* `openmp.sh`: Sbatch file to get wall time and memory needed for OpenMP codes
* `hybrid.sh`: Sbatch file to get wall time and memory needed for hybrid (OpenMP+MPI) codes
* `OpenMP_walltime_memory.txt`: Results from `openmp.sh`
* `Hybrid_walltime_memory.txt`: Results from `hybrid.sh`
* `prof_serial.out`: Results from profiling analysis of sequential/serial code

# How to run
* `OpenMP_walltime_memory.txt`: run with `sbatch openmp.sh`, then compile with `sacct --format="JobID,Elapsed,CPUTime,MaxRSS" --jobs=jobID>OpenMP_walltime_memory.txt`
* `Hybrid_walltime_memory.txt`: run with `sbtach hybrid.sh`, then compile with `sacct --format="JobID,Elapsed,CPUTime,MaxRSS" --jobs=jobID>Hybrid_walltime_memory.txt`
* `prof_serial.out`:  after you run `./serial.out <number of episodes> <episode length>`, get the profiling results by compiling `gprof ./serial.out > prof_serial.out`