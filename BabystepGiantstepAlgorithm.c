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
	ll i = -1, j = -1;
	ll m = sqrt((double) n - 1) + 1;

	ll *babyStepTable = (ll*) malloc(m * sizeof(ll));
	if (babyStepTable == NULL)
	{
		fprintf(stderr, "Allocating BabyStepTable failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug_printf("\tm: %llu\n", m);

	debug_printf("\tBabyStep ");
	for (j = 0; j < m; j++)
	{
		babyStepTable[j] = modpow(g, (ll) j, n);
	}
#ifdef DEBUG
	printTable(babyStepTable, m);
#endif

	debug_printf("\tGianStep [");
	for (i = 0; i < m; i++)
	{
		ll exp = ((n - m) - 1) * i;
		ll tmpErg = modpow(g, exp, n);
		ll result = mulmod(a, tmpErg, n);

		debug_printf("%llu,", result);

		for (j = 0; j < m; j++)
		{
			if (babyStepTable[j] == result)
			{
				debug_printf("\b]\n\n");
				goto out;
			}
		}
	}
out:
	free(babyStepTable);

	return i * m + j;
}

void printTable(ll *table, ll size)
{
	printf("[");
	int i;
	for (i = 0; i < size; i++)
	{
			printf("%llu,", table[i]);
	}
	printf("\b]\n");
}
