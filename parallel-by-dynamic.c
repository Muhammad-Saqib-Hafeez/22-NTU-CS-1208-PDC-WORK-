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
    int start = 1, end = 20; 
    unsigned long long results[end - start + 1]; 

    double start_time = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int i = start; i <= end; i++) {
        int thread_id = omp_get_thread_num(); 
        results[i - start] = factorial(i);
        printf("Thread %d calculated %d! = %llu\n", thread_id, i, results[i - start]);
    }

    double end_time = omp_get_wtime();

    // Print results
    printf("Factorials from %d to %d (Dynamic Scheduling):\n", start, end);
    for (int i = start; i <= end; i++) {
        printf("%d! = %llu\n", i, results[i - start]);
    }

    // Print execution time
    printf("Execution Time (Dynamic Scheduling): %f seconds\n", end_time - start_time);

    return 0;
}

/*
Remarks:
- Dynamic scheduling assigns loop iterations to threads as they become available.
- It is useful when the workload is uneven, as it ensures better load balancing.
- However, it introduces additional overhead due to the dynamic assignment of iterations.
- Suitable for problems where iterations have varying execution times.
*/