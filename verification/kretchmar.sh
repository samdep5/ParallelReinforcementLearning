mkdir kretchmar1
mkdir kretchmar4

# Run 1000 sequential experiments
for i in $(seq 1 1 1000)
do
OMP_NUM_THREADS=1 ../code/openmp.out 1000 1 > kretchmar1/sim${i}.out
done

# Run 1000 experiments in four-way parallel
for i in $(seq 1 1 1000)
do
OMP_NUM_THREADS=4 ../code/openmp.out 4000 1 > kretchmar4/sim${i}.out
done