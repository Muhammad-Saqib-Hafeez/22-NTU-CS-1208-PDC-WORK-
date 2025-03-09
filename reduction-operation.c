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

 
    unsigned long long sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = start; i <= end; i++) {
        int thread_id = omp_get_thread_num(); 
        unsigned long long fact = factorial(i);
        results[i - start] = fact;
        sum += fact;
        // printf("Thread %d calculated %d! = %llu\n", thread_id, i, results[i - start]);
    }

    double end_time = omp_get_wtime();

    // printf("Factorials from %d to %d (Reduction):\n", start, end);
    // for (int i = start; i <= end; i++) {
    //     printf("%d! = %llu\n", i, results[i - start]);
    // }

    printf("Sum of factorials: %llu\n", sum);

    printf("Execution Time (Reduction): %f seconds\n", end_time - start_time);

    return 0;
}

/*
Remarks:
- The reduction clause performs a reduction operation (e.g., sum, product) across threads.
- Each thread maintains a private copy of the reduction variable, and the results are combined at the end.
- It is efficient and avoids the need for critical sections or atomic operations.
- Suitable for problems involving associative and commutative operations (e.g., sum, product).
*/