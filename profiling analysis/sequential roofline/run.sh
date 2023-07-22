#!/bin/bash

module purge
module load gcc/10.2.0-fasrc01
module load openmpi/4.1.1-fasrc01

cd ../../code
make serial
cd ../profiling\ analysis/sequential\ roofline/
mv ../../code/serial.out .

source ~/intel/oneapi/setvars.sh

export TMPDIR=~/scratch_folder/ tmp

# intel advisor collects data
advixe-cl -collect roofline -project-dir ./ -- ./serial.out 512 100 > rst.txt
# above is equivalent to the following lines, which should be used when doing mpi
#advixe-cl -collect survey -project-dir ./ -- ./serial.out 512 100 > rst.txt
#advixe-cl -collect tripcounts -flop -project-dir ./ -- ./serial.out 512 100 > rst.txt

# get a snapshot; view and save to html with GUI on laptop
advixe-cl --snapshot --project-dir ./ --pack --cache-sources --cache-binaries -- ./roofline_snapshot

