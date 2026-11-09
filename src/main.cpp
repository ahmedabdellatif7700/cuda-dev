#include <mpi.h>
#include <iostream>
int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size == 1) std::cout << "One local rank: inter-rank/network/GPU-aware/RDMA measurements pending.\n";
    if (size >= 2)
    {
        int value = 42;
        if (rank == 0) MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        if (rank == 1)
        {
            MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Rank 1 received host payload: " << value << '\n';
        }
    }
    MPI_Finalize();
}
