#include <stdio.h>

int main()
{
    float sum = 0;
    for (int i = 1; i < 10001; ++i)
        sum += i;
    printf("%f\n", sum);
    return 0;
}
