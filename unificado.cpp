#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   int num_processes = 0;
   int process_id = 0;
   MPI_Status status;
   /* La etiqueta/tag es un identificador de conversacion*/
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];   
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   cout << "Hoy soy el proceso " << process_id << endl;
   if (process_id == 0) { // entonces eres el receptor
      int etiqueta = 101;
      int mensaje[5];
      int partner = 1;    
      cout << "Hola de receiver " << process_id << " en " << host_name << "\n";
      int numero_de_enteros_a_recibir = 5;
      MPI_Recv(&mensaje, 
               numero_de_enteros_a_recibir, 
               MPI_INT, 
               partner, 
               etiqueta, 
               MPI_COMM_WORLD, 
               &status);
      for (int i=0; i < numero_de_enteros_a_recibir; i++)
         cout << "Hola de receiver " << process_id << " recibi " << mensaje[i] << endl;
      cout << "Lo recibi de " << status.MPI_SOURCE;
   } else if (process_id == 1) { // entonces eres el emisor
      int etiqueta = 101;
      int mensaje[5] = {11, 12, 13, 14, 15};
      int partner = 0;    
      int numero_de_enteros_a_recibir = 5;
      MPI_Send(&mensaje, 
               numero_de_enteros_a_recibir, 
               MPI_INT, 
               partner, 
               etiqueta, 
               MPI_COMM_WORLD);
               cout << "I just send the array" << endl;
   } 
   
   MPI_Finalize();

   return 0;
}