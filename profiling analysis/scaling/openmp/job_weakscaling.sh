#!/usr/bin/env bash
#SBATCH --job-name=weak_scaling
#SBATCH --output=%x.out
#SBATCH --error=%x.err
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=32
#SBATCH --time=02:00:00
#SBATCH --partition=broadwell

module purge
module load gcc/10.2.0-fasrc01
module load openmpi/4.1.1-fasrc01

cd ../../../code/
make openmp
cd ../profiling\ analysis/scaling/openmp
mv ../../../code/openmp.out .

# weak scaling
for i in 1 2 4 8 16 32; do
    export OMP_NUM_THREADS=$i
    mkdir threads$i
    ./openmp.out $((512*i)) 100 > threads$i/rst_weakscaling.txt
done

# get all results together
grep Ela threads*/rst*weak* > elapsedtime_weakscaling.txt

