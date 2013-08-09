#include <stdio.h>
#include <inttypes.h>
#include <math.h>

uint64_t nth_triangle_number(uint64_t n)
{
    return n*(n+1) / 2;
}

uint64_t num_divisors(uint64_t n)
{
    uint64_t root = sqrt(n);
    uint64_t res = 2;
    for (uint64_t i = 2; i <= root+1; ++i) {        
        if (n % i == 0) {
            res += 2;
        }
    }
    return res;
}

int main()
{
    uint64_t n = 1;
    uint64_t tri_num = 1;
    uint64_t num_div = 1;
    for (; num_div <= 500; ++n) {
        tri_num = nth_triangle_number(n);
        num_div = num_divisors(tri_num);
    }
    printf("%ld\n", tri_num);
    return 0;
}


