#include <stdio.h>
#include <omp.h>

int a = 1;
int b = 2;
int c = 3;

#pragma omp threadprivate(b)

int main() {
    #pragma omp parallel firstprivate(c) num_threads(4)
    {
        int d = a + c;

        #pragma omp atomic
        a += 1;
        #pragma omp atomic
        a += 2;
        #pragma omp atomic
        d += 3;

        b = d;

    
        {
            printf("a = %d, b = %d, c = %d\n", a, b, c);
        }
    }

    return 0;
}