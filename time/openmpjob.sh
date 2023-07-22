#!/usr/bin/env bash
#SBATCH --job-name=openmp
#SBATCH --output=openmp_<%j>.out
#SBATCH --error=openmp_<%j>.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8
#SBATCH --time=04:00:00
#SBATCH --partition=broadwell

OMP_NUM_THREADS=8 srun ./openmp.out 131072 1; 
OMP_NUM_THREADS=8 srun ./openmp.out 65536 2; 
OMP_NUM_THREADS=8 srun ./openmp.out 32768 4; 
OMP_NUM_THREADS=8 srun ./openmp.out 16384 8; 
OMP_NUM_THREADS=8 srun ./openmp.out  8192 16; 
OMP_NUM_THREADS=8 srun ./openmp.out 4096 32; 
OMP_NUM_THREADS=8 srun ./openmp.out 2048 64; 
OMP_NUM_THREADS=8 srun ./openmp.out 1024 128; 
OMP_NUM_THREADS=8 srun ./openmp.out 512 256; 
OMP_NUM_THREADS=8 srun ./openmp.out 256 512; 
OMP_NUM_THREADS=8 srun ./openmp.out 128 1024;
OMP_NUM_THREADS=8 srun ./openmp.out 64 2048;
OMP_NUM_THREADS=8 srun ./openmp.out 32 4096;
OMP_NUM_THREADS=8 srun ./openmp.out 16 8192;
OMP_NUM_THREADS=8 srun ./openmp.out 8 16384;

# return the exit code of srun above
exit $?

