#include "Utilities.h"
#include "BabystepGiantstepAlgorithm.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 0

ll babystepGiantstepAlgorithm(ll n, ll g, ll a)
{
	int i, j;
	ll m = sqrt((double) n - 1) + 1;
	ll *babyStepTable = (ll*) malloc(m * sizeof(ll));
	if (babyStepTable == NULL)
	{
		fprintf(stderr, "Allocating BabyStepTable failed: %s\n", strerror(errno));
		goto out_alloc_failed;
	}
#if DEBUG == 1
	printf("\tm: %llu\n", m);
#endif
#if DEBUG == 1
	printf("\tBabyStep ");
#endif
	for (j = 0; j < m; j++)
	{
		babyStepTable[j] = modpow(g, (ll) j, n);
	}
#if DEBUG == 1
	printTable(babyStepTable, m);
#endif
#if DEBUG == 1
	printf("\tGianStep [");
#endif
	for (i = 0; i < m; i++)
	{
		ll exp = ((n - m) - 1) * i;
		ll tmpErg = modpow(g, exp, n);
		ll result = mulmod(a, tmpErg, n);
#if DEBUG == 1
		printf("%llu,", result);
#endif
		for (j = 0; j < m; j++)
		{
			if (babyStepTable[j] == result)
			{
#if DEBUG == 1
				printf("\b]\n\n");
#endif
				goto out;
			}
		}
	}
out:
	free(babyStepTable);
	return i * m + j;

out_alloc_failed:
	return -1;
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
