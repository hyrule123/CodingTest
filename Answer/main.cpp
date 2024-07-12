#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 17299 (오등큰수)
*/
#include <array>
constexpr int arrSize = 1'000'001;
std::array<int, arrSize> inputs;	//입력
std::array<int, arrSize> freqs;		//출현 빈도

struct elem { int val, idx; };
struct Stack {
	std::array<elem, arrSize> cont{};
	int _size = 0;

	bool empty() { return _size == 0; }
	int size() { return _size; }
	void pop() { --_size; }
	void push(int _val, int _idx) { cont[_size].val = _val; cont[_size].idx = _idx; ++_size; }
	elem& back() { return cont[_size - 1]; }

} stack;
std::array<int, arrSize> ans;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//stack 삽입 규칙: 현재 스택의 맨 끝 값의 빈도보다 작은 값만 넣는다
	//stack의 맨 뒤보다 높은 값을 발견했을 경우 그보다 낮은 값들을 전부 꺼내서 NGF를 계산
	int N; std::cin >> N;
	ans.fill(-1);

	for (int i = 1; i <= N; ++i) {
		std::cin >> inputs[i];
		++(freqs[inputs[i]]);
	}

	//stack에는 빈도를 기록
	for(int i = 1;i <= N; ++i){
		int curNumFreq = freqs[inputs[i]];

		//마지막 값보다 카운트가 큰값을 발견한경우: stack에서 작은 값을 모조리 꺼내서 답지 배열에 등록
		while (false == stack.empty() && stack.back().val < curNumFreq) {
			//답은 freq가 아닌 높은 빈도를 가졌던 수임
			ans[stack.back().idx] = inputs[i];
			stack.pop();
		}

		stack.push(curNumFreq, i);
	}

	for (int i = 1; i <= N; ++i) {
		std::cout << ans[i] << ' ';
	}

	return 0;
}