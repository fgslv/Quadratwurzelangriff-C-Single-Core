#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "BabystepGiantstepAlgorithm.h"
#include "Utilities.h"
#include "Debug.h"

#define MAX_TABLE_SIZE 134217728


ll babystepGiantstepAlgorithm(ll n, ll g, ll a)
{
	ll m = sqrt((double)n - 1) + 1;
	debug_printf("\tm: %llu\n", m);

	ll tableSize = (m < MAX_TABLE_SIZE) ? m : MAX_TABLE_SIZE;
	ll numberOfBSGSSteps = (m / tableSize);
	ll slidingWindowSize = tableSize;
	ll slidingWindowSizeLastIteration = m % tableSize;

	debug_printf("numberOfBSGSSteps = %llu, slidingWindowSize = %llu, slidingWindowSizeLastIteration = %llu\n",
			numberOfBSGSSteps, slidingWindowSize, slidingWindowSizeLastIteration);

	ll *babyStepTable = (ll*) malloc(tableSize * sizeof(ll));
	if (babyStepTable == NULL)
	{
		fprintf(stderr, "Allocating BabyStepTable failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	ll result = -1;
	int k;
	for (k = 0; k < numberOfBSGSSteps; ++k)
	{
		ll start = k * slidingWindowSize;
		ll end = start + slidingWindowSize;

		calcBabyStepTableSlidingWindow(babyStepTable, m, g, n, start, end);
		result = calcGiantStepAndCheckSlidingWindow(babyStepTable, m, g, n, a, slidingWindowSize);
		
		if (result != -1)
		{
			goto out;
		}
	}
	calcBabyStepTableSlidingWindow(babyStepTable, m, g, n, numberOfBSGSSteps*slidingWindowSize, m);
	result = calcGiantStepAndCheckSlidingWindow(babyStepTable, m, g, n, a, slidingWindowSize);

out:
	free(babyStepTable);
	return result;
}


void calcBabyStepTableSlidingWindow(ll* babyStepTable, ll m, ll g, ll n, ll start, ll end)
{
	ll j;

	debug_printf("\tBabyStep ");
	for (j = 0; j < (end-start); j++)
	{
		babyStepTable[j] = modpow(g, (ll) j+start, n);
	}
	printTable(babyStepTable, end-start);
}


ll calcGiantStepAndCheckSlidingWindow(ll* babyStepTable, ll m, ll g, ll n, ll a, ll babyStepTableSize)
{
	ll i = -1, j = -1, result = -1;

	debug_printf("\tGianStep [");
	for (i = 0; i < m; i++)
	{
		ll exp = ((n - m) - 1) * i;
		ll tmpErg = modpow(g, exp, n);
		ll res = mulmod(a, tmpErg, n);

		for (j = 0; j < babyStepTableSize; j++)
		{
			if (babyStepTable[j] == res)
			{
				result = i * m + j;
				debug_printf("%llu,",result);
#ifndef NDEBUG
				goto out;
#endif
			}
		}
	}
out:
	debug_printf("\b]\n\n");
	return result;
}


void printTable(ll *table, ll size)
{
	debug_printf("[");
	int i;
	for (i = 0; i < size; i++)
	{
			debug_printf("%llu,", table[i]);
	}
	debug_printf("\b]\n");
}
