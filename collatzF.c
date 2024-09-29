#include "collatzF.h"
#include "cache.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int collatzSteps(int n)
{
    int steps = 0;
    while (n != 1)
    {
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

void runCollatzLRU(int N, int MIN, int MAX)
{
    srand(time(NULL));
    int cacheHits = 0;
    for (int i = 0; i < N; i++)
    {
        int RN = MIN + rand() % (MAX - MIN);
        CacheEntryLRU* entry = getFromCache(RN);
        int steps;
        if (entry == NULL)
        {
            steps = collatzSteps(RN);
            addToCacheLRU(RN, steps);
        }
        else
        {
            steps = entry->value;
            cacheHits++;
        }
        printf("%d,%d\n", RN, steps);
    }
    double cacheHitPercentage = ((double)cacheHits / N) * 100;
    printf("Cache Hit Percentage: %.2f%%\n", cacheHitPercentage);
}

void runCollatzLFU(int N, int MIN, int MAX)
{
    srand(time(NULL));
    int cacheHits = 0;
    for (int i = 0; i < N; i++)
    {
        int RN = MIN + rand() % (MAX - MIN);
        CacheEntryLFU* entry = getFromCacheLFU(RN);
        int steps;
        if (entry == NULL)
        {
            steps = collatzSteps(RN);
            addToCacheLFU(RN, steps);
        }
        else
        {
            steps = entry->value;
            cacheHits++;
        }
        printf("%d,%d\n", RN, steps);
    }
    double cacheHitPercentage = ((double)cacheHits / N) * 100;
    printf("Cache Hit Percentage: %.2f%%\n", cacheHitPercentage);
}