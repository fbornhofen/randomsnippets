#include <stdio.h>

int main()
{
    int a, b, c;
    for (a = 0; a < 500; ++a) {
        for (b = a; b < 500; ++b) {
            for (c = b; c < 500; ++c) {
                if (a*a + b*b == c*c) {
                    if (a + b + c == 1000) {
                        printf("%d * %d * %d = %d\n", a, b, c, a*b*c);
                    }
                }
            }
        }
    }
    return 0;
}
