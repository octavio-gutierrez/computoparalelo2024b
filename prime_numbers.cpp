#include <iostream>
#include <mpi.h>
#include <cmath>
#include <chrono>

using namespace std;

int prime_number(int n, int id, int num_processes) {
  int prime;
  int total = 0;
  for (int possible_prime = 2 + id; possible_prime <= n; possible_prime += num_processes) {
    prime = 1;
    int maximum = (int) trunc(sqrt(possible_prime));
    for (int divisor=2; divisor <= maximum; divisor++) {
      if ((possible_prime % divisor) == 0) {
        prime = 0;
        break;
      }
    }
    total += prime;
  }
  return total;
}


int main (int argc, char *argv[]) {
  int id;
  int num_processes;
  double wall_time;
  long long int n = 10;
  int total_primes = 0;
  int my_num_primes = 0;

  MPI_Init (&argc, &argv);
  MPI_Comm_size (MPI_COMM_WORLD, &num_processes);
  MPI_Comm_rank (MPI_COMM_WORLD, &id);
  
  while (n <= 1000000000) {
    if (id == 0) wall_time = MPI_Wtime();

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    my_num_primes = prime_number(n, id, num_processes);

    MPI_Reduce(&my_num_primes, &total_primes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (id == 0) {
      wall_time = MPI_Wtime() - wall_time;
      cout << "  " <<  n
           << "  " <<  total_primes
           << "  " <<  wall_time << endl;
    }
    n *= 10;
  }
  
  MPI_Finalize ( );
  return 0;
}

/* Serial version */
/*
int serial_prime_number(int n) {
  int prime;
  int total = 0;
  for (int possible_prime = 2; possible_prime <= n; possible_prime++) {
    prime = 1;
    int maximum = (int) trunc(sqrt(possible_prime));
    for (int divisor=2; divisor <= maximum; divisor++) {
      if ((possible_prime % divisor) == 0) {
        prime = 0;
        break;
      }
    }
    total += prime;
  }
  return total;
}

int main (int argc, char *argv[]) {
  
  long long int n = 10;
  int total_primes = 0;
  while (n <= 1000000000) {
    auto start = chrono::high_resolution_clock::now();    
    total_primes = serial_prime_number(n);
    auto end = chrono::high_resolution_clock::now();    
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "  " <<  n
         << "  " <<  total_primes
         << "  " <<  (float)duration.count()/1000000 << endl;  
    n *= 10;
  } 
  return 0;
}
*/
