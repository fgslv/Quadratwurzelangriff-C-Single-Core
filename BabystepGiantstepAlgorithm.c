#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Utilities.h"
#include "BabystepGiantstepAlgorithm.h"
#include "Debug.h"


ll babystepGiantstepAlgorithm(ll n, ll g, ll a)
{
	ll i = -1, j = -1, result = -1;

	ll m = sqrt((double)n - 1) + 1;
	debug_printf("\tm: %llu\n", m);

	ll *babyStepTable = (ll*) malloc(m * sizeof(ll));
	if (babyStepTable == NULL)
	{
		fprintf(stderr, "Allocating BabyStepTable failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	calcBabyStepTable(babyStepTable, m, g, n);
	result = calcGiantStepAndCheck(babyStepTable, m, g, n, a);

	free(babyStepTable);
	return result;
}

void calcBabyStepTable(ll* babyStepTable, ll m, ll g, ll n)
{
	ll j;
	debug_printf("\tBabyStep ");
	for (j = 0; j < m; j++)
	{
		babyStepTable[j] = modpow(g, (ll) j, n);
	}
	printTable(babyStepTable, m);
}

ll calcGiantStepAndCheck(ll* babyStepTable, ll m, ll g, ll n, ll a)
{
	ll i, j, result;

	debug_printf("\tGianStep [");
	for (i = 0; i < m; i++)
	{
		ll exp = ((n - m) - 1) * i;
		ll tmpErg = modpow(g, exp, n);
		ll res = mulmod(a, tmpErg, n);

		for (j = 0; j < m; j++)
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
