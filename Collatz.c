#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include "collatzF.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <N> <MIN> <MAX>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);
    runCollatzLRU(N, MIN, MAX);
    //runCollatzLFU(N, MIN, MAX);
    return 0;
}