#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "collatzF.h"

int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        printf("Usage: %s <N> <MIN> <MAX> <none, lru, lfu> <CACHE_SIZE>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);
    char policy[5];
    char* NONE = "none";
    char* LRU = "lru";
    char* LFU = "lfu";
    strncpy(policy, argv[4], sizeof(policy) - 1);
    policy[sizeof(policy) - 1] = '\0';
    int cache = atoi(argv[5]);

    if (strcmp(NONE, policy) == 0)
    {
        runCollatz(N, MIN, MAX);
    }
    else if (strcmp(LRU, policy) == 0)
    {
        setCacheValueLRU(cache);
        runCollatzLRU(N, MIN, MAX);
    }
    else if (strcmp(LFU, policy) == 0)
    {
        setCacheValueLFU(cache);
        runCollatzLFU(N, MIN, MAX);
    }
    else
    {
        printf("Error occurred! No valid policy set.\n");
        return 1;
    }
    return 0;
}