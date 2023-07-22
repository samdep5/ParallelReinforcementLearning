# team07

* Team supervisor is Iris: yye@g.harvard.edu

## Organization

* `code`: All our code.  See subordinate README file in that folder for details of individual files and how to run them.
* `time`: The timed versions, outputs, and job scripts for determining synchronization frequency.
* `graphics`: Graphics for our report.
* `milestone`: Milestones.
* `profiling analysis`: Profiling analysis data, rooflines (see the readme file in the `sequential roofline` folder), scaling analysis (see the readme file in the `scaling` folder), and so forth.
* `verification`: Tools to generate figures to check our code's numerical results against Kretchmar's.  First run `kretchmar.sh` and then execute the `kretchmar_results_process.nb` notebook in Mathematica.
    * **Note:** To exactly copy Kretchmar's work, first set `mangle_count` to `0` in `code/bandit.cpp`.

