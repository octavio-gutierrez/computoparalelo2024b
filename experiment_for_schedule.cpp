#include <omp.h>
#include <iostream>
#include <iomanip>
#include <chrono>


using namespace std;

int main (int argc, char** argv) {
	//std::cout << std::fixed << std::setprecision(2);

    bool static_behavior = true;
	long long int vector_size = 0;
    int number_threads = 0;
        
    // test values
	// long long int vector_size = 1000000000;
    // bool static_behavior = true;

	if (argc == 1) {
		cout << "No se pasaron argumentos " << argv[0];
		return 0;
	} else {
		cout << " Ingresaste " << argc - 1  << " argumentos" << "\n";
		if (argc > 2) {
			vector_size = atol(argv[1]);
            static_behavior = atoi(argv[2]);
		}
	}

	float* a = new float[vector_size];
	float* b = new float[vector_size];
	float* c = new float[vector_size];

    const int num_chunk_sizes = 9;
    int chunk_sizes[num_chunk_sizes] = {1, 10, 20, 40, 80, 160, 320, 640, 1280};
    
    const int num_thread_pools = 4;
    int thread_pools[num_thread_pools] = {1, 3, 6, 12};

	for (long long int i = 0; i < vector_size; i++)
		a[i] = b[i] = i * 1.0;
	
	double start; 
	double end; 
    int tid = 0;

    // serial version for reference
    auto start_serial = std::chrono::high_resolution_clock::now();
    for (long long int i = 0; i < vector_size; i++) {
        c[i] = a[i] + b[i];
    }    
    auto end_serial = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<chrono::microseconds>(end_serial - start_serial);
    double serial_time = (double)duration.count()/1000000;
    cout << serial_time << "\n";  // <<" seconds\n";


    for (int nthreads = 0; nthreads < num_thread_pools; nthreads++) {
        omp_set_num_threads(thread_pools[nthreads]);
        for (int chunk = 0; chunk < num_chunk_sizes; chunk++) {
            int chunk_size = chunk_sizes[chunk];
            start = omp_get_wtime(); 
            #pragma omp parallel shared(static_behavior, chunk_size) private (tid)
            {
                if (static_behavior) {
                    #pragma omp for schedule(static, chunk_size) 
                    for (long long int i = 0; i < vector_size; i++) {
                            c[i] = a[i] + b[i];
                            // tid = omp_get_thread_num();
                            // #pragma omp critical
                            // cout << "Thread id: " << tid << " c[" << i << "] = " << c[i] << " static\n";
                    }
                } else {
                    #pragma omp for schedule(dynamic, chunk_size) 
                    for (long long int i = 0; i < vector_size; i++) {
                            c[i] = a[i] + b[i];
                            // tid = omp_get_thread_num();
                            // #pragma omp critical
                            // cout << "Thread id: " << tid << " c[" << i << "] = " << c[i] << " dynamic\n";
                    }
                }
            }
            end = omp_get_wtime(); 
            cout << thread_pools[nthreads] << "," << chunk_size << "," << serial_time / (end - start)  << "\n";  // <<" seconds\n";
        }	
    }

	delete[] a;
	delete[] b;
	delete[] c;
}