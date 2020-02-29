#include <mpi.h>
#include <cstdio>
#include <cstdlib>


#define comm MPI_COMM_WORLD
FILE* f;

const int lmax = 10;

int main(int argc, char **argv)
{
	int size, rank, msgtag = 5, pr = 1, id, dest;
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

	for (int l = 0; l < lmax; l++)
	{
		int Ocount = 0, Hcount = 0, h2oCount = 0;
		if (!rank)
		{
			for (int i = 1; i < size; i++)
			{
				MPI_Recv(&pr, 1, MPI_INT, i, msgtag, comm, &status);

				if (pr)
				{
					MPI_Recv(&pr, 1, MPI_INT, i, msgtag, comm, &status);
					//dest = status.MPI_SOURCE;
				}
				else
				{
					pr = 1;
					MPI_Recv(&pr, 1, MPI_INT, 0, msgtag, comm, &status);
				}
			}
		}
		else
		{
			pr = rand() % 2;
			MPI_Send(&pr, 1, MPI_INT, 0, msgtag, comm);
			if (rank % 2) id = 1; // Hydrogen
			else id = 0; // Oxygen
			MPI_Send(&id, 1, MPI_INT, 0, msgtag, comm);

			MPI_Recv(&pr, 1, MPI_INT, 0, msgtag, comm, &status);
		}
	}


	MPI_Barrier(comm);
	MPI_Finalize();
	return 0;
}
