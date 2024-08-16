#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 12852(1로 만들기 2)
//참고문항: 1463번 (1로 만들기) 복습
*/
/* 아이디어
1부터 시작
1을 더하기, 2를 곱하기, 3을 더하기 -> 먼저 N에 도착하면 그 경로를 출력
경로 기록 방법: 최단거리가 갱신될 때 해당 최단거리를 어떤 연산으로 도달했는지 기록
*/
constexpr int arrSize = (int)1e6 + 1;
enum class e { add1, mul2, mul3 };
struct trail {
	int shortestCount; //가장 적은 연산횟수
	e type;	//어떤 연산을 통해서 값에 도달했는지
};
trail dp[arrSize]; 
int N;

inline void memo(int idx, int val, e type) {
	if (idx <= N && val < dp[idx].shortestCount) {
		dp[idx].shortestCount = val;
		dp[idx].type = type;
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N;
	for (int i = 0; i <= N; ++i) {
		dp[i].shortestCount = (int)1e9;
	}
	dp[1].shortestCount = 0;
	for (int i = 1; i < N; ++i) {
		int next = dp[i].shortestCount + 1;

		memo(i + 1, next, e::add1);
		memo(i * 2, next, e::mul2);
		memo(i * 3, next, e::mul3);
	}
	int shortest = dp[N].shortestCount;
	std::cout << shortest << '\n';

	//연산 기록을 타고 1까지 내려간다.
	for (int i = N; i >= 1;) {
		std::cout << i << ' ';

		switch (dp[i].type)
		{
		case e::add1:
			i -= 1;
			break;
		case e::mul2:
			i /= 2;
			break;
		case e::mul3:
			i /= 3;
			break;
		default:
			break;
		}
	}

	return 0;
}