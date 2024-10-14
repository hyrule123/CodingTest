#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() { 
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <vector>
#include <string>
#include <stack>
std::vector<std::vector<int>> LCS;
std::string s1, s2;

void solve()
{
	s1 = " ";
	s2 = " ";
	std::string input;
	std::cin >> input;
	s1 += input;
	std::cin >> input;
	s2 += input;

	//row: s1, col: s2
	LCS.resize(s1.size(), std::vector<int>(s2.size(), 0));

	for (size_t i = 1; i < s1.size(); ++i) {
		for (size_t j = 1; j < s2.size(); ++j) {
			//동일 값을 발견한 경우 대각선 방향 + 1
			if (s1[i] == s2[j]) {
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
			}
			//동일 값이 없는 경우 r-1 혹은 c-1에서 큰 값을 들고온다
			else {
				LCS[i][j] = std::max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
	}

	int LCS_len = LCS.back().back();
	std::stack<char> reverse;
	int r = (int)s1.size() - 1, c = (int)s2.size() - 1;
	while (reverse.size() < LCS_len) {
		//우선순위는 상관없다. 위 또는 왼쪽에 동일값이 있을 경우 이동
		if (LCS[r - 1][c] == LCS[r][c]) {
			--r;
		}
		else if (LCS[r][c - 1] == LCS[r][c]) {
			--c;
		}
		else {
			reverse.push(s1[r]);
			--r; --c;
		}
	}

	std::cout << reverse.size() << '\n';
	while (false == reverse.empty()) {
		std::cout << reverse.top(); reverse.pop();
	}
}
