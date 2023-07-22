# Files

In each folder `hybrid` and `openmp`, there are two batch scripts used to perform strong and weak scaling analysis for the hybrid MPI-OpenMP case and the OpenMP-only case.  There is also a plotting script in each folder to create the strong and weak scaling figures.

* `job_strongscaling.sh`: An example batch script to perform strong scaling analysis.  The script compiles our code first, move the executable into the corresponding folder, run strong scaling tests on the broadwell partition, and collect the elapsed times.
* `job_weakscaling.sh`: Similar to the strong scaling script, but doing weak scaling analysis.
* `plot.py`: Used to produce strong and weak scaling figures.
* `WeakEfficiency.ipynb`: Used to produce weak efficiency figure.

# How to run

`sbatch` the corresponding scripts and plot using `plot.py`.

