#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 17298 (오큰수) - 고정배열 버전(13740kb, 188ms)
*/
struct elem { int val, idx; };
struct Stack {
	elem cont[1'000'000]{};
	int size{};

	bool Empty() { return size == 0; }
	void Push(int _val, int _idx) { cont[size].val = _val; cont[size].idx = _idx; ++size; }
	void Pop() { --size; }
	elem& Back() { return cont[size - 1]; }
};
Stack stack;
#include <array>
std::array<int, 1'000'000> ans;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//stack 삽입 규칙: 현재 스택의 맨 끝 값보다 낮은 값만 넣는다.
	//높은 값을 발견했을 경우 그보다 낮은 값들을 전부 꺼내서 NGE를 계산
	int N; std::cin >> N;
	ans.fill(-1);

	for (int i = 0; i < N; ++i) {
		int input; std::cin >> input;

		//stack이 비어있지 않고 마지막 값보다 큰값을 발견한경우: stack에서 작은 값을 모조리 꺼내서 답지 배열에 등록
		while (false == stack.Empty() && stack.Back().val < input) {
			ans[stack.Back().idx] = input;
			stack.Pop();
		}

		stack.Push(input, i);
	}

	for (int i = 0; i < N; ++i) {
		std::cout << ans[i] << ' ';
	}

	return 0;
}