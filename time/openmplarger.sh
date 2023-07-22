#!/usr/bin/env bash
#SBATCH --job-name=openmp
#SBATCH --output=openmp_<%j>.out
#SBATCH --error=openmp_<%j>.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8
#SBATCH --time=04:00:00
#SBATCH --partition=broadwell

# here we run our program: see man srun
OMP_NUM_THREADS=8 srun ./openmp.out 16777216 1; 
OMP_NUM_THREADS=8 srun ./openmp.out 8388608 2; 
# Only made to here before it timed out but was able to look at the first two results compare to one another
OMP_NUM_THREADS=8 srun ./openmp.out 4194304 4; 
OMP_NUM_THREADS=8 srun ./openmp.out 2097152 8; 
OMP_NUM_THREADS=8 srun ./openmp.out 1048576 16; 
OMP_NUM_THREADS=8 srun ./openmp.out 524288 32; 
OMP_NUM_THREADS=8 srun ./openmp.out 262144 64; 
OMP_NUM_THREADS=8 srun ./openmp.out 131072 128; 
OMP_NUM_THREADS=8 srun ./openmp.out 65536 256; 
OMP_NUM_THREADS=8 srun ./openmp.out 32768 512; 
OMP_NUM_THREADS=8 srun ./openmp.out 16384 1024; 
OMP_NUM_THREADS=8 srun ./openmp.out  8192 2048; 
OMP_NUM_THREADS=8 srun ./openmp.out 4096 4096; 
OMP_NUM_THREADS=8 srun ./openmp.out 2048 8192; 
OMP_NUM_THREADS=8 srun ./openmp.out 1024 16384; 
OMP_NUM_THREADS=8 srun ./openmp.out 512 32768; 
OMP_NUM_THREADS=8 srun ./openmp.out 256 65536; 
OMP_NUM_THREADS=8 srun ./openmp.out 128 131072;
OMP_NUM_THREADS=8 srun ./openmp.out 64 262144;
OMP_NUM_THREADS=8 srun ./openmp.out 32 524288;

# return the exit code of srun above
exit $?


