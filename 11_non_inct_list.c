#include <stdio.h>

int main(void)
{
    long n, new, old, i;
    int c;
    int flag = 1;
    (void)scanf("%ld", &n);
    (void)scanf("%ld", &old);
    for(i = 0; i < n - 1; ++i)
    {
        (void)scanf("%ld", &new);
        (old < new) ? (old = new, c = 0) : (old = new, c = 1);
        if ((c == 0)) flag = 0;
    }
    printf("%d", flag);
    return 0;
}
