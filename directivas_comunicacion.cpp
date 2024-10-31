#include <mpi.h>
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
   const int MASTER = 0;
   int num_processes = 0;
   int process_id = 0; 
   int name_length = 0;
   char host_name[MPI_MAX_PROCESSOR_NAME];
   
   int my_message = 0;
   int sender_id = MASTER;
   int receiver_id = MASTER;
   const int NUM_VECTORS = 3;
   const int VECTOR_SIZE = 5;
   float data[NUM_VECTORS][VECTOR_SIZE] = {{11, 12, 13, 14, 15},
                                           {16, 17, 18, 19, 20},
                                           {21, 22, 23, 24, 25}};
   float message[VECTOR_SIZE];
   float data_to_be_collected[NUM_VECTORS] = {0, 0, 0};



   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
   MPI_Get_processor_name(host_name, &name_length);

   if (num_processes == NUM_VECTORS) {
      if (process_id == MASTER)
         cout << "Repartiendo los vectores de la matriz";      
      MPI_Scatter(&data, VECTOR_SIZE, MPI_FLOAT, 
                  &message, VECTOR_SIZE, MPI_FLOAT, sender_id, 
	               MPI_COMM_WORLD);
      cout << "Proceso " << process_id << " " << message[0]
                                       << " " << message[1]
                                       << " " << message[2]
                                       << " " << message[3]
                                       << " " << message[4]
                                       << endl;

      // cada uno de los hilos calcula la suma de su renglon
      float total = 0.0;
      for (int i = 0; i < VECTOR_SIZE; i++) {
         total += message[i];
      } 
      cout << "Proceso " << process_id << " mi total es " << total << endl;
      
      MPI_Gather(&total, 1, MPI_FLOAT, 
	              &data_to_be_collected, 1, MPI_FLOAT, receiver_id, 
	              MPI_COMM_WORLD); 

      cout << "Proceso " << process_id << " recolecte " << data_to_be_collected[0] 
                                                        << data_to_be_collected[1] 
                                                        << data_to_be_collected[2] << endl;
      float reduction_result = 0;   
      MPI_Reduce(&total, &reduction_result, 1, MPI_FLOAT, MPI_MIN, receiver_id, 
	              MPI_COMM_WORLD); 

      if (process_id == receiver_id) 
         cout << "Reduction result " << reduction_result << endl;

   } else {
      cout << "El numero de procesos debe ser igual al numero de vectores" << endl;
   }

/*
   if (process_id == MASTER) {
      cout << "MASTER: The number of MPI processes is " << num_processes << "\n";
      my_message = 8;
   }
   cout << "Soy " << process_id << " tengo variable my_message " << my_message << endl;   
   MPI_Bcast(&my_message, 1, MPI_INT, sender_id, MPI_COMM_WORLD);
   cout << "Soy " << process_id << " recibi " << my_message << " de " << sender_id << endl;   

*/
   
   MPI_Finalize();

   return 0;
}