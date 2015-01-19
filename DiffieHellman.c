#include "Utilities.h"
#include "DiffieHellman.h"

void diffieHellman(ll n, ll g, ll x, ll y, ll *a, ll *b, ll *k)
{
	*a = modpow(g, x, n);
	*b = modpow(g, y, n);
	*k = modpow(*a, y, n);
}
