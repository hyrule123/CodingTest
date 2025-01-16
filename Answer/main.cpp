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
백준 23797 (개구리) [그리디]
현재 K가 필요한 개구리와 P가 필요한 개구리를 카운트
K가 필요한데 K가 필요한 개구리가 없다? 그럼 개구리 수 하나 증가시키고 P가 필요한 개구리 카운트 증가
반대(P가 필요한데...)도 마찬가지
*/
#include <string>
#include <stack>
stack<char> stk;
string input;
int frog, waiting_for_K, waiting_for_P;

void solve() 
{
	cin >> input;
	input[0] == 'K' ? waiting_for_P++ : waiting_for_K++;
	frog = 1;
	for (size_t i = 1; i < input.size(); ++i)
	{
		if (input[i] == 'K')
		{
			if (waiting_for_K == 0)
			{
				frog++;
			}
			else
			{
				waiting_for_K--;
			}
			waiting_for_P++;
		}
		else //P
		{
			if (waiting_for_P == 0)
			{
				frog++;
				
			}
			else
			{
				waiting_for_P--;
			}
			waiting_for_K++;
		}
	}

	cout << frog;
}