#include <stdio.h>
#include <omp.h>

// Function to compute factorial
unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int start = 1, end = 10000; 
    unsigned long long results[end - start + 1]; 

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = start; i <= end; i++) {
        int thread_id = omp_get_thread_num(); 
        results[i - start] = factorial(i);
        // printf("Thread %d calculated %d! = %llu\n", thread_id, i, results[i - start]);
    }

    double end_time = omp_get_wtime();

    // printf("Factorials from %d to %d:\n", start, end);
    // for (int i = start; i <= end; i++) {
    //     printf("%d! = %llu\n", i, results[i - start]);
    // }

    printf("Execution Time (Parallel): %f seconds\n", end_time - start_time);

    return 0;
}

/*
Remarks:
- Workload evenly distributed among the threads.
*/
