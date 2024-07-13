#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 3015 (오아시스 재결합)
*/
#include <array>
using ll = long long;
constexpr ll arrSize = 500000;
//500000명이 있고 모두 같은 키일때 경우의 수: 500000 * 499999 / 2
//124,999,750,000 -> 1000억이 넘어감
struct man { ll height, sameHeightCount; };
struct Stack {
	std::array<man, arrSize> cont{};
	ll size = 0;

	bool Empty() { return size == 0; }
	ll Size() { return size; }
	man& Back() { return cont[size - 1]; }
	void Push(const man& h) { cont[size] = h; ++size; }
	void Pop() { --size; }
	void Clear() { size = 0; }
} stack;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	ll N; std::cin >> N;

	ll pairCount = 0;
	for(ll i =0;i<N;++i){
		man cur; std::cin >> cur.height;
		cur.sameHeightCount = 1;
		
		/*
		stack 삽입 규칙
		1. 스택은 항상 내림차순이여야 한다.
		2. 이번에 들어갈 원소가 1번 규칙을 깰 경우(스택의 끝보다 클 경우)
				-> 규칙에 맞을 때까지 스택을 꺼내고, pairCount를 기록된 sameHeightCount만큼 더해준다.
			 ex) 3 3 3 + 4 -> 3/4 3/4 3/4 3개 경우의수가 만들어짐
		3. 만약 이번에 들어갈 원소가 스택의 끝과 같다면 병합한다(sameHeightCount를 그만큼 늘려준다)
			-> 병합 전 pairCount를 sameHeightCount만큼 늘려준다.(
			ex. 3 + 3 -> pairCount에 1 더해주고 둘이 병합 -> 3(2)
				3(2) + 3 -> pairCount에 2 더해주고 병합 3(3)
				-->> 3 3 3 은 서로를 볼 수 있는 쌍이 3개 만들어진다.
			3-1. 만약 병합한 원소 앞에 원소가 하나 더 있을경우 1만큼 더해준다(
			ex. 4 3(2) + 3 -> 4/3 쌍이 하나 생기므로 +1
		*/

		while (false == stack.Empty() && stack.Back().height < cur.height) {
			pairCount += stack.Back().sameHeightCount;
			stack.Pop();
		}

		if (false == stack.Empty()) {
			//맨 끝 사람과 키가 같을경우
			if (stack.Back().height == cur.height) {
				pairCount += stack.Back().sameHeightCount;
				cur.sameHeightCount += stack.Back().sameHeightCount;
				stack.Pop();

				//사람이 남아있어 쌍을 이룰 수 있을경우
				if (false == stack.Empty()) {
					++pairCount;
				}
			}
			//맨 끝 사람보다 키가 작을경우
			else {
				++pairCount;
			}
		}

		stack.Push(cur);
	}
	std::cout << pairCount;

	return 0;
}