# Files

* `run.sh`: Use this example script to run roofline analysis on the sequential code with Intel Advisor.
* `roofline_snapshot.html`: A roofline snapshot saved after running Intel Advisor on an interactive node and viewing the results on laptop.

# How to run

Check out a compute node, e.g. `salloc -N1 -c64 -t 01:00:00`, and do `bash run.sh`.  You need to have intel advisor installed in your home directory, however.  Then download the roofline snapshot file to your local computer, view with the Intel Advisor GUI, and save to html.  For some misterious reasons, Intel Advisor gives errors when run on the broadwell node so our roofline analysis was not done on broadwell.

