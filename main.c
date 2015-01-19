#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Utilities.h"
#include "DiffieHellman.h"
#include "BabystepGiantstepAlgorithm.h"

void help(void);
void readInput(char *argv[], ll *n, ll *g, ll *a, ll *b);
void printValues(ll n, ll g, ll x, ll y);


int main(int argc, char* argv[])
{
	ll n, g, x, y;

	if (argc != 5)
	{
		help();
		exit(0);
	}
	else 
	{
		readInput(argv, &n, &g, &x, &y);
		printValues(n, g, x, y);
	}

	ll a, b, key_alice_bob;
	diffieHellman(n, g, x, y, &a, &b, &key_alice_bob);

	printf("\nAlice sends:\t %llu\n", a);
	printf("Bob sends:\t %llu\n", b);
	printf("Secret Key:\t %llu\n\n", key_alice_bob);
	
	ll _x, _y;
	clock_t start = clock();
	_x = babystepGiantstepAlgorithm(n, g, a);
	_y = babystepGiantstepAlgorithm(n, g, b);
	clock_t finish = clock();

	if (-1 == _x || -1 == _y)
	{
		exit(EXIT_FAILURE);
	}

	ll key_charlie;
	diffieHellman(n, g, _x, _y, &a, &b, &key_charlie);
	printf("Charlie determined the secret key %llu in %fsec.\n\n", key_charlie, ((double)(finish - start) / CLOCKS_PER_SEC));
	
	exit(0);
}

void help(void)
{
	fprintf(stdout, "usage: quadratwurzelangriff n g x y\n");
}

void readInput(char *argv[], ll *n, ll *g, ll *a, ll *b)
{
	*n = strtoull(argv[1], NULL, 10 );
	*g = strtoull(argv[2], NULL, 10 );
	*a = strtoull(argv[3], NULL, 10 );
	*b = strtoull(argv[4], NULL, 10 );

	*a = (*a >= *n) ? (*a % *n) : *a;
	*b = (*b >= *n) ? (*b % *n) : *b;
}

void printValues(ll n, ll g, ll a, ll b)
{
	printf("Safe Prime:\t\t%llu\n", n);	
	printf("Primitive Prime:\t%llu\n", g);
	printf("Alice thinks of:\t%llu\n", a);
	printf("Bob thinks of:\t\t%llu\n", b);
}
