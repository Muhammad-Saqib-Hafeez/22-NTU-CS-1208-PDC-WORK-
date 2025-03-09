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

    #pragma omp parallel for schedule(static)
    for (int i = start; i <= end; i++) {
        int thread_id = omp_get_thread_num(); 
        results[i - start] = factorial(i);
        // printf("Thread %d calculated %d! = %llu\n", thread_id, i, results[i - start]);
    }

    double end_time = omp_get_wtime();

    // printf("Factorials from %d to %d (Static Scheduling):\n", start, end);
    // for (int i = start; i <= end; i++) {
    //     printf("%d! = %llu\n", i, results[i - start]);
    // }

    printf("Execution Time (Static Scheduling): %f seconds\n", end_time - start_time);

    return 0;
}

/*
Remarks:
- Static scheduling divides the loop iterations into equal-sized chunks and assigns them to threads.
- It is efficient when the workload is evenly distributed.
- However, if the workload is uneven, some threads may finish earlier and remain idle.
- Suitable for problems where each iteration takes approximately the same amount of time.
*/