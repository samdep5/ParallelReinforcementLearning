#!/usr/bin/env bash
#SBATCH --job-name=openmp
#SBATCH --output=hybrid_<%j>.out
#SBATCH --error=hybrid_<%j>.err
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --time=04:00:00
#SBATCH --partition=broadwell

 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 131072 1; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 65536 2; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 32768 4; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 16384 8; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out  8192 16; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 4096 32; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 2048 64; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 1024 128; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 512 256; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 256 512; 
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 128 1024;
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 64 2048;
OMP_NUM_THREADS=8 srun -n4 -c8 ./hybrid.out 32 4096;

# return the exit codeof srun above
exit $