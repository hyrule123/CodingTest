#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 9252 (LCS 2) : LCS 문제에 역추적 추가
*/
/*
* https://seongjuk.tistory.com/entry/%EC%B5%9C%EC%9E%A5-%EA%B3%B5%ED%86%B5-%EB%B6%80%EB%B6%84-%EC%88%98%EC%97%B4-LCS-Longest-Common-Subsequence-%EA%B3%BC-%EC%97%AD%EC%B6%94%EC%A0%81
* -> 요 사이트가 제일 잘 이해가는듯
* 2차원 DP 배열을 사용.
* dp[i][j] : A 문자열의 i번째까지 문자열과 B 문자열의 j번째까지 문자열로 만들 수 있는 부분 문자열의 최장 길이
*/
char a[1002], b[1002];
int dp[1002][1002], len_a, len_b;

#include <stack>

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//한칸 띄고 읽어준다.
	//0번째는 널문자가 아닌 아무 문자로 채워준다
	a[0] = '_'; b[0] = '_';
	std::cin.getline(a + 1, 1001);
	std::cin.getline(b + 1, 1001);

	//길이 가져옴(0번째 문자는 제외)
	len_a = (int)strlen(a) - 1;
	len_b = (int)strlen(b) - 1;

	for (int i = 1; i <= len_a; ++i) {
		for (int j = 1; j <= len_b; ++j) {
			//같은 문자를 발견한 경우 dp[i-1][j-1]의 값 + 1을 해준다.
			if (a[i] == b[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			//다른 문자일 경우 이전 문자열 중 큰 값을 가져온다.
			else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	//역추적
	std::stack<char> ans;
	int i = len_a, j = len_b;
	while (i >= 1 && j >= 1) {
		//[i][j-1] 또는 [i-1][j]와 [i][j]가 같은 경우: 이 문자는 LCS에 포함되지 않았다.
		//포함되면 +1이 되므로
		if (dp[i][j] == dp[i][j - 1]) {
			--j;
		}
		else if (dp[i][j] == dp[i - 1][j]) {
			--i;
		}

		//다른 경우: LCS에 포함되었음 -> 좌측 상단 대각선 방향으로 이동
		else {
			ans.push(a[i]);
			--i; --j;
		}
	}

	std::cout << ans.size() << '\n';
	while (false == ans.empty()) {
		std::cout << ans.top(); ans.pop();
	}

	return 0;
}