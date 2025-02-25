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
백준 11571(분수를 소수로) [수학]
https://chatgpt.com/share/67bcf20a-bad8-8001-973a-6936e66a77f0
1. 정수 부분을 계산(진분수로 만들기)
2. 기약분수 만들기
3. 유한소수 부분 구하기
4. 순환소수 부분 구하기
*/
#include <string>
#include <vector>

int GCD(int a, int b)
{
	while (b != 0)
	{
		int r = a % b;
		a = b; 
		b = r;
	}
	return a;
}

void solve()
{
	int T; cin >> T;
	string output;
	while (T--)
	{
		output.clear();

		//정수 부분 계산
		int nom, denom; cin >> nom >> denom;

		output += to_string(nom / denom);
		if (nom / denom) { nom %= denom; }
		output += '.';

		
		//기약분수로 변환
		while (true)
		{
			int gcd = GCD(nom, denom);
			if (gcd == 1) { break; }
			nom /= gcd;
			denom /= gcd;
		}
		
		//유한소수 부분
		//분모를 소인수분해 했을 때, 2^a * 5^b * ... 형태에서
		//max(a, b)가 비순환소수 부분의 자리수이다.
		/*
		* GPT 답변
		혼순환소수의 비순환(즉, 소수점 아래 처음에 나타나는 유한한) 부분의 길이는 분수를 기약분수로 만들었을 때 분모에 포함된 2와 5의 지수에 따라 결정됩니다.
		예를 들어, 기약분수 b / a 에서
		b=2^α × 5^β × c(c는 2와 5와 공약수가 없음)
		라고 나타낼 수 있습니다. 
		이때 소수로 나타낼 때 비순환 부분의 자릿수는
		max(α,β)
		*/
		int test = denom, exp_2 = 0, exp_5 = 0;
		while (test % 2 == 0)
		{
			test = test / 2;
			exp_2++;
		}
		while (test % 5 == 0)
		{
			test = test / 5;
			exp_5++;
		}

		//순환소수 자릿수만큼 진행
		for (int i = 0; i < max(exp_2, exp_5); ++i)
		{
			if (nom == 0) { break; }

			nom *= 10;
			output += to_string(nom / denom);
			nom %= denom;
		}
		
		//순환소수 부분
		output += '(';

		//2와 5가 제거된 분모가 1이 아닐 경우 순환이 있는 것
		if (nom != 0 && test != 1)
		{
			//순환하는 부분의 자릿수는 10^n % test 의 나머지가 1이 되는 시점의 n
			int cycle_len = 1, base = 10;
			while (base % test != 1)
			{
				base = base % test;
				base *= 10;
				++cycle_len;
			}

			for (int i = 0; i < cycle_len; ++i)
			{
				nom *= 10;
				output += to_string(nom / denom);
				nom %= denom;
			}
		}
		else
		{
			output += '0';
		}

		output += ')';
		cout << output << '\n';
	}
}