#ifndef BABYSTEP_GIANTSTEP_ALGORITHM_H_
#define BABYSTEP_GIANTSTEP_ALGORITHM_H_

ll babystepGiantstepAlgorithm(ll n, ll g, ll a);
void calcBabyStepTable(ll* babyStepTable, ll m, ll g, ll n);
ll calcGiantStepAndCheck(ll* babyStepTable, ll m, ll g, ll n, ll a);
void printTable(ll *table, ll size);

#endif
