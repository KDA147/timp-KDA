#include <stdio.h>

int main(void)
{
    long n, new, old, i;
    (void)scanf("%ld", &n);
    (void)scanf("%ld", &old);
    for(i = 0; i < n - 1; ++i)
    {
        (void)scanf("%ld", &new);
        old = (old < new) ? old : new;
    }
    printf("%ld", old);
    return 0;
}