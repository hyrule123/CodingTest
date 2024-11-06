#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

using namespace std;
int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <vector>
#include <string>
int N, K;
string numbers[16];
int dp[1 << 16][16];

//모든 경우의 수를 살펴봐야 하므로 완전탐색은 필수
//a, b 두 수를 이어붙인 ab는 a * 10^(b의 자릿수) + b
//1. a, b 두 수 모두 나누어 떨어질 때: ab도 나누어 떨어짐
//2. a, b 두 수 모두 나누어 떨어지지 않을때: ab도 나누어떨어지지 않음
//3. a, b 둘 중 하나만 나누어떨어질 때: ab는 나누어떨어질수도 있음
// 10^(b의 자릿수)이 K로 나누어 떨어질 때
//	11, 12를 붙인 1112를 4로 나눌 경우: 277

void solve() {
	cin >> N;
	numbers.resize(N);
	for (int i = 0; i < N; ++i) {
		cin >> numbers[i];
	}
	cin >> K;

}