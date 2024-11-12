#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

//백준 1305 (광고)
//문제 설명이 좀 어려운데, 쉽게 풀어쓰면
//현재 광고판에 나오고 있는 문자열을 표현할 수 있는 가장 짧은 문자열 이다. 
// babba, 5 -> bab로 babba를 만들 수 이씅ㅁ
#include <string>
#include <vector>
int L;
string S;
constexpr int arr_len = 'z' - 'a' + 1, INF = 987654321;
int memo[arr_len];

vector<int> build_failure_func() {
	vector<int> ret; ret.resize(L, 0);

	int j = 0;
	for (int i = 1; i < L; ++i) {
		while (0 < j && S[i] != S[j]) {
			j = ret[j - 1];
		}

		if (S[i] == S[j]) {
			ret[i] = ++j;
		}
	}

	return ret;
}

void solve() {
	for (int i = 0; i < arr_len; ++i) {
		memo[i] = 987654321;
	}

	cin >> L; S.reserve(L + 1);
	cin >> S;

	vector<int> fail_func = build_failure_func();

	L -= fail_func.back();

	cout << L;
}