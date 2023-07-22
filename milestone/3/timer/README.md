* `agent.cpp`: Our original sequential baseline.  Compile with `make serial`.
* `agent_openmp.cpp`: Agents parallelized with only OpenMP.  Compile with `make openmp`.
* `agent_openmp_mpi.cpp`: Agents parallelized with OpenMP and MPI.  Compile with `make hybrid`.
* `agent_generic.cpp`: Generic agent code that works the same whether it's sequential or parallel.
* `bandit.cpp`: The bandit.  Exactly the same in the sequential or parallel setting.
* `history.cpp`: Our implementation of a levelled history, as described in the writeup.
