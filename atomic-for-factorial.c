#include <stdio.h>
#include <omp.h>

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
        unsigned long long fact = factorial(i);
        #pragma omp atomic write
        results[i - start] = fact;
        // printf("Thread %d calculated %d! = %llu\n", thread_id, i, results[i - start]);
    }

    double end_time = omp_get_wtime();

    // Print results
    // printf("Factorials from %d to %d (Atomic Operation):\n", start, end);
    // for (int i = start; i <= end; i++) {
    //     printf("%d! = %llu\n", i, results[i - start]);
    // }

    // Print execution time
    printf("Execution Time (Atomic Operation): %f seconds\n", end_time - start_time);

    return 0;
}

/*
Remarks:
- The atomic operation ensures that a specific memory location is updated atomically (without race conditions).
- It is less expensive than a critical section but can only be used for simple operations (e.g., read, write, update).
- Suitable for protecting single shared variables.
*/