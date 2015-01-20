#ifndef BABYSTEP_GIANTSTEP_ALGORITHM_H_
#define BABYSTEP_GIANTSTEP_ALGORITHM_H_

typedef unsigned long long ll;

ll babystepGiantstepAlgorithm(ll n, ll g, ll a);
void calcBabyStepTableSlidingWindow(ll* babyStepTable, ll m, ll g, ll n, ll start, ll end);
ll calcGiantStepAndCheckSlidingWindow(ll* babyStepTable, ll m, ll g, ll n, ll a, ll babyStepTableSize);
void printTable(ll *table, ll size);

#endif
