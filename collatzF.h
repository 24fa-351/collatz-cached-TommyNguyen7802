#ifndef COLLATZF_H
#define COLLATZF_H

int collatzSteps(int n);
void runCollatz(int N, int MIN, int MAX);
void runCollatzLRU(int N, int MIN, int MAX);
void runCollatzLFU(int N, int MIN, int MAX);

#endif