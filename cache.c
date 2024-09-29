#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

CacheEntryLRU* cache[CACHE_SIZE];
CacheEntryLRU* head;
CacheEntryLRU* tail;
CacheEntryLFU* cacheLFU[CACHE_SIZE];
int cacheCount;

CacheEntryLRU* getFromCache(int key)
{
    for (int i = 0; i < cacheCount; i++)
    {
        if (cache[i]->key == key)
        {
            if (cache[i] != head)
            {
                if (cache[i] == tail)
                {
                    tail = cache[i]->prev;
                    tail->next = NULL;
                }
                else
                {
                    cache[i]->prev->next = cache[i]->next;
                    cache[i]->next->prev = cache[i]->prev;
                }
                cache[i]->next = head;
                cache[i]->prev = NULL;
                head->prev = cache[i];
                head = cache[i];
            }
            return cache[i];
        }
    }
    return NULL;
}

void addToCacheLRU(int key, int value)
{
    CacheEntryLRU* newEntry = (CacheEntryLRU*)malloc(sizeof(CacheEntryLRU));
    newEntry->key = key;
    newEntry->value = value;
    newEntry->prev = NULL;
    newEntry->next = head;
    if (head != NULL)
    {
        head->prev = newEntry;
    }
    head = newEntry;
    if (tail == NULL)
    {
        tail = newEntry;
    }
    if (cacheCount < CACHE_SIZE)
    {
        cache[cacheCount++] = newEntry;
    }
    else
    {
        CacheEntryLRU* oldTail = tail;
        tail = tail->prev;
        tail->next = NULL;
        free(oldTail);
        cache[cacheCount - 1] = newEntry;
    }
}

CacheEntryLFU* getFromCacheLFU(int key)
{
    for (int i = 0; i < cacheCount; i++)
    {
        if (cacheLFU[i]->key == key)
        {
            cacheLFU[i]->frequency++;
            return cacheLFU[i];
        }
    }
    return NULL;
}

void addToCacheLFU(int key, int value)
{
    if (cacheCount < CACHE_SIZE)
    {
        cacheLFU[cacheCount] = (CacheEntryLFU*)malloc(sizeof(CacheEntryLFU));
        cacheLFU[cacheCount]->key = key;
        cacheLFU[cacheCount]->value = value;
        cacheLFU[cacheCount]->frequency = 1;
        cacheCount++;
    }
    else
    {
        int minFreq = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < CACHE_SIZE; i++)
        {
            if (cacheLFU[i]->frequency < minFreq)
            {
                minFreq = cacheLFU[i]->frequency;
                minIndex = i;
            }
        }
        cacheLFU[minIndex]->key = key;
        cacheLFU[minIndex]->value = value;
        cacheLFU[minIndex]->frequency = 1;
    }
}