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
make openmp
cd ../profiling\ analysis/scaling/openmp
mv ../../../code/openmp.out .

# strong scaling
for i in 1 2 4 8 16 32; do
    export OMP_NUM_THREADS=$i
    mkdir threads$i
    ./openmp.out 512 100 > threads$i/rst_strongscaling.txt
done

# get all results together
grep Ela threads*/rst*str* > elapsedtime_strongscaling.txt

