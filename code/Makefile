serial: agent.cpp
	g++ -pg -O3 -o serial.out agent.cpp

openmp: agent_openmp.cpp
	g++ -O3 -fopenmp -o openmp.out agent_openmp.cpp

hybrid: agent_openmp_mpi.cpp
	mpic++ -O3 -fopenmp -o hybrid.out agent_openmp_mpi.cpp

clean:
	rm -f *.out