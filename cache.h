#ifndef CACHE_H
#define CACHE_H

typedef struct CacheEntryLRU
{
    int key;
    int value;
    struct CacheEntryLRU* prev;
    struct CacheEntryLRU* next;
} CacheEntryLRU;

typedef struct CacheEntryLFU
{
    int key;
    int value;
    int frequency;
} CacheEntryLFU;

void setCacheValueLRU(int cache);
CacheEntryLRU* getFromCache(int key);
void addToCacheLRU(int key, int value);
void setCacheValueLFU(int cache);
CacheEntryLFU* getFromCacheLFU(int key);
void addToCacheLFU(int key, int value);
#endif