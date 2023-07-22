#!/usr/bin/env bash
#SBATCH --job-name=hybrid
#SBATCH --output=hybrid_<%j>.out
#SBATCH --error=hybrid_<%j>.err
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --time=00:10:00
#SBATCH --partition=broadwell

# set the number of OpenMP threads per MPI process
# (more on this in class later)
export OMP_NUM_THREADS=32

# here we run our program: see man srun
srun ./hybrid.out 512 100

# return the exit code of srun above
exit $?