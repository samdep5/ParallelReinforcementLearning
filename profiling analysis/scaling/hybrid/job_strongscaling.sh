#!/usr/bin/env bash
#SBATCH --job-name=strong_scaling
#SBATCH --output=%x.out
#SBATCH --error=%x.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --time=01:00:00
#SBATCH --partition=broadwell

module purge
module load gcc/10.2.0-fasrc01
module load openmpi/4.1.1-fasrc01

cd ../../../code/
make hybrid
cd ../profiling\ analysis/scaling/hybrid
mv ../../../code/hybrid.out .

# 1 thread
export OMP_NUM_THREADS=1
for i in 1 2 4 8 16 32; do
    dir=n${i}_threads$OMP_NUM_THREADS
    mkdir $dir
    srun -n $i -c $OMP_NUM_THREADS ./hybrid.out 512 100 > $dir/rst_strongscaling.txt
done

# 2 threads
export OMP_NUM_THREADS=2
for i in 1 2 4 8 16; do
    dir=n${i}_threads$OMP_NUM_THREADS
    mkdir $dir
    srun -n $i -c $OMP_NUM_THREADS ./hybrid.out 512 100 > $dir/rst_strongscaling.txt
done

# 4 threads
export OMP_NUM_THREADS=4
for i in 1 2 4 8; do
    dir=n${i}_threads$OMP_NUM_THREADS
    mkdir $dir
    srun -n $i -c $OMP_NUM_THREADS ./hybrid.out 512 100 > $dir/rst_strongscaling.txt
done

# get all results together
grep Ela n*threads*/rst*str* > elapsedtime_strongscaling.txt

