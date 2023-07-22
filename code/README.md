# Files

* `agent.cpp`: Our original sequential baseline.  Compile with `make serial`.
* `agent_openmp.cpp`: Agents parallelized with only OpenMP.  Compile with `make openmp`.
* `agent_openmp_mpi.cpp`: Agents parallelized with OpenMP and MPI.  Compile with `make hybrid`.
* `agent_generic.cpp`: Generic agent code that works the same whether it's sequential or parallel.
* `bandit.cpp`: The bandit.  Exactly the same in the sequential or parallel setting.
* `history.cpp`: Our implementation of a levelled history, as described in the writeup.

# How to run

Our code has three separate implementations of the same RL algorithm.

* **Serial:** compile with `make serial` to get `serial.out` and then run `./serial.out <number of episodes> <episode length>`.
* **OpenMP:** compile with `make openmp` to get `openmp.out` and then run `OMP_NUM_THREADS=<number of threads> ./openmp.out <number of episodes> <episode length>`.
* **OpenMP and MPI hybrid:** compile with `make hybrid` to get `hybrid.out` and then run `OMP_NUM_THREADS=<number of OpenMP threads> mpirun -n <number of MPI cores> ./hybrid.out <number of episodes> <episode length>`.

The number of episodes passed in is the number of total episodes, not the number of episodes per agent.  (This is a philosophical departure from Kretchmar's work.)  Running `OMP_NUM_THREADS=2 ./openmp.out 500 200` will spawn two agents simultaneously.  Each will execute 250 episodes of 200 actions each, and the agents will synchronize with each other after each episode.

Whatever option you choose, the output will consist of one line per agent per episode of the form `<OpenMP thread index> <Episode number per agent> <Total reward for episode> <Fraction of episode actions that were optimal>`, separated by tabs.  There will then be a blank line, a line of the form `<Total reward for all episodes> <Fraction of total actions that were optimal>`, again separated by tabs, and finally profiling information.
