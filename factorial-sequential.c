#include <stdio.h>
#include <time.h>

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

    clock_t start_time = clock();
    for (int i = start; i <= end; i++) {
        results[i - start] = factorial(i);
    }
    clock_t end_time = clock();

    printf("Factorials from %d to %d:\n", start, end);
    for (int i = start; i <= end; i++) {
        printf("%d! = %llu\n", i, results[i - start]);
    }
    printf("Execution Time (Sequential): %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}

