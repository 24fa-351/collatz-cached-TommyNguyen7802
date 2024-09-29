#ifndef CACHE_H
#define CACHE_H

#define CACHE_SIZE 10000

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


CacheEntryLRU* getFromCache(int key);
void addToCacheLRU(int key, int value);
CacheEntryLFU* getFromCacheLFU(int key);
void addToCacheLFU(int key, int value);
#endif