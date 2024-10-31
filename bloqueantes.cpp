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
   int partner = -1;

   if (process_id < num_processes/2) { // soy un proceso izquierdo
      int etiqueta = 101;
      int mensaje = 8;
      partner = process_id + num_processes/2;   
      int numero_de_enteros_a_enviar = 1;
      MPI_Send(&mensaje, 
               numero_de_enteros_a_enviar, 
               MPI_INT, 
               partner, 
               etiqueta, 
               MPI_COMM_WORLD);
               cout << "I just send and int value" << endl;
      int numero_de_enteros_a_recibir = 1;
      MPI_Recv(&mensaje, 
               numero_de_enteros_a_recibir, 
               MPI_INT, 
               partner, 
               etiqueta, 
               MPI_COMM_WORLD, 
               &status);                  
   } else { // process_id >= num_processes/2 -> soy derecho
      int etiqueta = 101;
      int mensaje = 8;
      partner = process_id - num_processes/2;   
      int numero_de_enteros_a_enviar = 1;
      int numero_de_enteros_a_recibir = 1;
      MPI_Recv(&mensaje, 
               numero_de_enteros_a_recibir, 
               MPI_INT, 
               partner, 
               etiqueta, 
               MPI_COMM_WORLD, 
               &status);                  
      MPI_Send(&mensaje, 
               numero_de_enteros_a_enviar, 
               MPI_INT, 
               partner, 
               etiqueta, 
               MPI_COMM_WORLD);
               cout << "I just send and int value" << endl;
   }
   
   cout << "Hoy soy el proceso " << process_id << " con partner " << partner <<  endl;
   
   MPI_Finalize();

   return 0;
}