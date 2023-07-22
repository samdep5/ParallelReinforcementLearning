# Parallel Reinforcement Learning

See the paper for this project in `report.pdf` or the presentation in `presentation.pdf` for the clearest, most complete information and results.

This repository contains a project using OpenMp and MPI for a parallelized reinforcement learning algorithm that learns faster than the standard. This speed improvement and parallelization is done via a levelled history (detailed in `report.pdf` or `presentation.pdf`). This project was completed by Sam DePaolo, Michael Kielstra, Manqing Liu, and Xiaohan Wu as the final research project in CS205 (High Performance Computing) and builds upon work introduced by Kretchmar.

## Organization

* `code`: All our code.  See subordinate README file in that folder for details of individual files and how to run them.
* `time`: The timed versions, outputs, and job scripts for determining synchronization frequency.
* `graphics`: Graphics for our report.
* `profiling analysis`: Profiling analysis data, rooflines (see the readme file in the `sequential roofline` folder), scaling analysis (see the readme file in the `scaling` folder), and so forth.
* `verification`: Tools to generate figures to check our code's numerical results against Kretchmar's.  First run `kretchmar.sh` and then execute the `kretchmar_results_process.nb` notebook in Mathematica.
    * **Note:** To exactly copy Kretchmar's work, first set `mangle_count` to `0` in `code/bandit.cpp`.
