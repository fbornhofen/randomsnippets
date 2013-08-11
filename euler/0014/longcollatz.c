#include <stdio.h>
#include <inttypes.h>

uint64_t collatz_length(uint64_t n)
{
    uint64_t len = 0;
    for (;;) {
        ++len;
        if (n == 1) {
            return len;
        }
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = n*3 + 1;
        }
    }
}

int main(int argc, char** argv)
{
    uint64_t argmax = 1;
    uint64_t maxlen = 0;
    uint64_t curlen = 0;
    uint64_t i;
    for (i = 1; i < 1000000; ++i) {
        curlen = collatz_length(i);
        if (curlen > maxlen) {
            argmax = i;
            maxlen = curlen;
        }
    }
    printf("%" PRIu64 " (%" PRIu64 ")\n", argmax, collatz_length(argmax));
    return 0;
}
