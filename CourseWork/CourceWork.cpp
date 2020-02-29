#include <mpi.h>
#include <cstdio>


#define comm MPI_COMM_WORLD
FILE* f;

int main(int argc, char **argv)
{
	int size, rank, msgtag = 5;
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
		return 1;
	if (MPI_Comm_size(MPI_COMM_WORLD, &size) != MPI_SUCCESS)
	{
		MPI_Finalize();
		return 2;
	}
	if (MPI_Comm_rank(MPI_COMM_WORLD, &rank) != MPI_SUCCESS)
	{
		MPI_Finalize();
		return 3;
	}
	
	MPI_Status status;

	if (!rank)
	{
		
	}
	else
	{
		
	}
	
	MPI_Barrier(comm);
	MPI_Finalize();
	return 0;
}