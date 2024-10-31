#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   int messages[2] = {111, 999};
   MPI_Request request[4];
   MPI_Status status[4];      

   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   cout << "Hi from processes " << process_id << " on " << host_name << "\n";

   if (process_id == MASTER) 
      cout << "MASTER: The number of MPI processes is " << num_processes << "\n";

   // partners caso general
   int left = process_id - 1;
   int right = process_id + 1;
   // partners casos especificos
   if (process_id == 0) {
      left = num_processes - 1;
   }
   if (process_id == (num_processes - 1)) {
      right = 0;
   }

   // recepciones no bloqueantes
   MPI_Irecv(&messages[0], 1, MPI_INT, left, 101, MPI_COMM_WORLD, &request[0]);
   cout << "Soy proceso " << process_id << " puse un escuchador para la izquierda " << messages[0] << endl;

   MPI_Irecv(&messages[1], 1, MPI_INT, right, 102, MPI_COMM_WORLD, &request[1]);
   cout << "Soy proceso " << process_id << " puse un escuchador para la derecha  " << messages[1] << endl;

   // envios no bloquantes
   MPI_Isend(&process_id, 1, MPI_INT, left, 102, MPI_COMM_WORLD, &request[2]);
   cout << "Soy proceso " << process_id << " envie mensaje a la izquierda " << left << endl;

   MPI_Isend(&process_id, 1, MPI_INT, right, 101, MPI_COMM_WORLD, &request[3]);
   cout << "Soy proceso " << process_id << " envie mensaje a la derecha " << right << endl;
   
   int i = 0;
   while (i < 50) {
      cout << " Proceso " << process_id << " perdiendo el tiempo " << endl;
      i++;
   }

   MPI_Waitall(4, request, status);

   cout << " Proceso " << process_id << " recibi mensaje " << messages[0] << endl;
   cout << " Proceso " << process_id << " recibi mensaje " << messages[1] << endl;


   MPI_Finalize();

   return 0;
}