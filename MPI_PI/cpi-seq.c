#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

main(int argc, char **argv)
{
  double width, sum, mysum;
  int intervals = 5, i, mynpts;
  int rc, myid, nprocs;
  MPI_Status Stat;
  /* get the number of intervals */

  /*
  * Feature added by @crolopez
  *
  */
  intervals = atoi(argv[1]);
  width = 1.0 / intervals;
  rc = MPI_Init(&argc,&argv);
  //MPI_INIT(ierr);
  if (rc != MPI_SUCCESS){
    printf("Error inicializando MPI, abortando.\n");
    MPI_Abort(MPI_COMM_WORLD, rc);
  }
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);
  /* do the computation */
  mysum = 0.0;
  for (i=myid; i<intervals; i+=nprocs) {
    register double x = (i + 0.5) * width;
    mysum += 4.0 / (1.0 + x * x);
  }
  MPI_Reduce(&mysum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
  if(myid == 0){
  	printf("Estimation of pi is %f\n", sum);
  }
  MPI_Finalize();
  return(0);
}
