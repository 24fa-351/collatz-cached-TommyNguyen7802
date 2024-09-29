#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

int cache_size;
CacheEntryLRU** cacheLRU;
CacheEntryLRU* head;
CacheEntryLRU* tail;
CacheEntryLFU** cacheLFU;
int cacheCount;

void setCacheValueLRU(int cache)
{
    cache_size = cache;
    cacheLRU = (CacheEntryLRU**)malloc(cache * sizeof(CacheEntryLRU*));
    for (int i = 0; i < cache_size; i++) {
        cacheLRU[i] = NULL;
    }
}

void setCacheValueLFU(int cache)
{
    cache_size = cache;
    cacheLFU = (CacheEntryLFU**)malloc(cache * sizeof(CacheEntryLFU*));
    for (int i = 0; i < cache_size; i++) {
        cacheLFU[i] = NULL;
    }
}

CacheEntryLRU* getFromCache(int key)
{
    for (int i = 0; i < cacheCount; i++)
    {
        if (cacheLRU[i]->key == key)
        {
            if (cacheLRU[i] != head)
            {
                if (cacheLRU[i] == tail)
                {
                    tail = cacheLRU[i]->prev;
                    tail->next = NULL;
                }
                else
                {
                    cacheLRU[i]->prev->next = cacheLRU[i]->next;
                    cacheLRU[i]->next->prev = cacheLRU[i]->prev;
                }
                cacheLRU[i]->next = head;
                cacheLRU[i]->prev = NULL;
                head->prev = cacheLRU[i];
                head = cacheLRU[i];
            }
            return cacheLRU[i];
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
    if (cacheCount < cache_size)
    {
        cacheLRU[cacheCount++] = newEntry;
    }
    else
    {
        CacheEntryLRU* oldTail = tail;
        tail = tail->prev;
        tail->next = NULL;
        free(oldTail);
        cacheLRU[cacheCount - 1] = newEntry;
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
    if (cacheCount < cache_size)
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
        for (int i = 0; i < cache_size; i++)
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