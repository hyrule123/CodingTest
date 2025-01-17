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
백준 26111 (Parentheses Tree) [그래프]
* 풀이 1. 문자열의 앞부터 전위순회 한다는 느낌으로 접근
	( 뒤에 또 (가 들어오면 앞의 ( 노드는 리프노드가 아니다.
*/

#include <string>
#include <vector>
string input;
vector<bool> stk;

void solve()
{
	cin >> input;
	stk.reserve(input.size());
	stk.push_back(true);
	//반드시 루트를 가지는 트리라고 했으니까 예외 처리는 안해도 될듯
	size_t dist_sum = 0;
	for (int i = 1; i < (int)input.size(); ++i)
	{
		char cur = input[i];
		if (cur == '(') {
			//( 다음에 (가 왔으므로 바로 전 노드는 리프노드가 아님
			stk.back() = false;
			stk.push_back(true);
		}
		else// ')'
		{
			//리프노드 발견
			if (stk.back() == true)
			{
				dist_sum += stk.size() - 1;
			}
			stk.pop_back();
		}
	}
	cout << dist_sum;
}
