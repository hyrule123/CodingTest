#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;
void solve();
int main()
{
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

/*
백준 13172(Σ) [나머지]
* 모듈로 곱셈의 항등원: a * b ≡ a (mod X) 를 만족시키는 b
	-> b = 1
* 모듈로 곱셈의 역원 
	a * b ≡ 1 (mod X) 를 만족시키는 b
	이 때 b를 a^-1로 표현
* 현재 mod를 소수로 사용하고 있으므로, 페르마의 소정리를 사용할 수 있다.
	a^(X - 1) ≡ 1 (mod X)
	-> a^(X - 2) ≡ a^(-1) (mod X)
* 모듈러 곱셈의 역원과 일반 곱셈의 역원이 다른 이유
	-> 모듈러는 항상 정수 형태이고, 일반 곱셈은 실수이기 때문
	a^(-1)인 1 / a는 a가 1이 아닐때는 모듈러 곱셈 역원이 될수 없다
*/
#include <unordered_map>
using ull = unsigned long long;
constexpr ull mod = 1'000'000'007;
ull M, nom, denom = 1;

ull GCD(ull a, ull b)
{
	//a = bx + r
	while (b != 0)
	{
		ull r = a % b;
		a = b;
		b = r;
	}
	return a;
}

ull fastpowmod(ull base, ull exp)
{
	if (exp == 0) { return 1; }

	ull ret = exp & 1 ? base % mod : 1;
	ull curmul = base % mod;
	for (ull i = 1; i < 64; ++i)
	{
		curmul = (curmul * curmul) % mod;
		if (exp & (1ull << i))
		{
			ret = (ret * curmul) % mod;
		}
	}
	return ret % mod;
}

void solve()
{
	cin >> M;
	for (ull i = 0; i < M; ++i)
	{
		ull N, S; cin >> N >> S;

		//기약분수 형태로 전환
		while (true)
		{
			ull gcd = GCD(S, N);
			if (gcd == 1) { break; }
			S /= gcd;
			N /= gcd;
		}

		/*
		a	c	ad + bc
		- * - = -------
		b	d	  bd
		*/

		nom = ((nom * N) % mod + (S * denom) % mod) % mod;
		denom = (denom * N) % mod;
	}

	ull ans = (nom * fastpowmod(denom, mod - 2)) % mod;
	cout << ans;
}