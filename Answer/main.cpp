#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 17298 (오큰수) - std::vector 버전(29376kb, 184ms)
*/
#include <vector>
struct elem { int val, idx; };
std::vector<elem> stack;
std::vector<int> ans;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//stack 삽입 규칙: 현재 스택의 맨 끝 값보다 낮은 값만 넣는다.
	//높은 값을 발견했을 경우 그보다 낮은 값들을 전부 꺼내서 NGE를 계산
	int N; std::cin >> N;
	stack.reserve(N); ans.resize(N, -1);

	for (int i = 0; i < N; ++i) {
		int input; std::cin >> input;
		if (stack.empty()) { stack.push_back({ input, i }); }

		//마지막 값보다 큰값을 발견한경우: stack에서 작은 값을 모조리 꺼내서 답지 배열에 등록
		while (false == stack.empty() && stack.back().val < input) {
			ans[stack.back().idx] = input;
			stack.pop_back();
		}

		stack.push_back({ input, i });
	}

	for (int i = 0; i < N; ++i) {
		std::cout << ans[i] << ' ';
	}

	return 0;
}