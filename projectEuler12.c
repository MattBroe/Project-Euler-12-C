#include <stdio.h>
#include <stdlib.h>

// Project Euler 12
// Matt Broe

// Prompt: Find the least triangular number with more than 500 divisors.

// The solution relies on the fact that d(a*b) = d(a)d(b) when gcd(a, b) = 1. To find
// d(n(n+1)/2), it suffices to find d(n) and d((n+1)/2) (or d(n/2) and d(n+1),
// if n is even), since the factors n and (n+1)/2 are coprime. It also
// uses the expression of d(n) in terms of the prime factorization of n: d(n) =
// product of (a_i + 1), where a_i is the highest power of the i_th prime
// that divides n. In order for the numDivisors function to use this 
// expression to compute d(n), the main method must iteratively build 
// an array of primes which it passes to numDivisors.


int numDivisors(int n, int* primeList, int numPrimes);

int main()
{

	int* primeList = malloc(500*sizeof(int));
	*(primeList) = 2;
	int numPrimes = 1; 
	// we need to keep track of the number of primes in primeList in order 
	// to resize it when it fills up
	int primeListSize = 500;

	int x = 2;
	int a; int b;

	while (1) {
		x += 1;
		if (x % 2 == 0) {
			a = numDivisors(x / 2, primeList, numPrimes);
			b = numDivisors(x-1, primeList, numPrimes);
		}
		else {
			a = numDivisors(x, primeList, numPrimes);
			b = numDivisors((x-1)/2, primeList, numPrimes);
			if (a == 2) {
				numPrimes += 1;
				*(primeList + (numPrimes-1)) = x;
			}
		}

		if (numPrimes == primeListSize) {
			primeList = realloc(primeList, (primeListSize + 50)*sizeof(int));
			primeListSize += 50;
		}

		if (a*b > 500) {
			printf("%d * %d / 2 = %d is the least triangular number with more than 500 divisors\n", x-1, x, (x*(x-1))/2);
			break;
		}
	}
		free(primeList);
	}



// The primeList must contain all the primes less than n for numDivisors to
// work properly.


int numDivisors(int n, int* primeList, int numPrimes)
{
	int p;
	int power;
	int currentNumDivisors = 1;
	for (int i = 0; i < numPrimes; i++) {
		p = *(primeList + i);
		power = 0;
		while (n % p == 0) {
			n = n / p;
			power += 1;
		}
		currentNumDivisors *= (power + 1);
	}

	if (currentNumDivisors == 1){
		//then n is prime
		currentNumDivisors += 1;
	}

	return currentNumDivisors;
}
