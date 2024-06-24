#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

//스택 활용 풀이
using ll = long long;
struct Bar { ll idx, height; };
struct Stack {
	Stack() : cont{}, size{}, cursor{ -1 } {}
	~Stack() { delete[] cont; }

	bool Empty() { return (cursor < 0); }
	void PushBack(const Bar& _elem) { ++cursor; cont[cursor] = _elem; }
	const Bar& Back() { return cont[cursor]; }
	void PopBack() { if (0 <= cursor) { --cursor; } }
	void Reset(ll _size) { 
		if (size < _size) { 
			if (cont) { delete[] cont; }
			cont = new Bar[_size];
		}
		size = _size;
		cursor = -1;
	}

	Bar* cont;
	ll size;
	ll cursor;
};

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;
	
	Stack stack;
	while (true) {
		ll N; std::cin >> N;
		if (N == 0) { break; }
		stack.Reset(N);
		
		ll maxSquare = 0;
		for (ll i = 0; i < N; ++i) {
			ll inputHeight; std::cin >> inputHeight;

			//stack 삽입 규칙: 자신보다 작은 막대가 들어올 경우 stack에서 그것보다 더 긴 막대를 모두 제거
			//-> 쉽게 말해서 오름차순을 유지
			//긴 막대를 제거하면서(stack 왼쪽으로 이동하면서), 오른쪽으로 만들 수 있는 최대 직사각형을 탐색

			/*
			stack이 비어있지 않고, 
			이번 입력으로 들어온 막대의 높이가 스택에 있는 마지막 막대보다 짧을 경우
			하나씩 꺼내면서 이 막대로 만들수 있는 최대 직사각형 넓이를 계산한다.
			예시 (idx, height)
			1-1. stack (0, 5) (1, 9) / inputHeight (2, 5)
			(1, 9)를 꺼내서 9로 만들수있는 최대 직사각형을 계산
			2번 인덱스에서 시작해서 0번 인덱스에서 가로막힘 -> 1개
			-> 9 * (2 - (0 + 1)) = 9
			자신보다 큰 막대만 제거하므로 (0, 5)에서 중단하고 스택에 (2, 5) 삽입

			1-2. stack (0, 5) (2, 5) /inputHeight (3, 2)
			(2, 5)를 꺼내서 만들수 있는 최대 직사각형을 계산 -> 5 * (3 - (0 + 1)) = 10
			그 다음 5도 이번 height인 2보다 크므로 최대 직사각형 계산(stack이 비어있으므로 최대 길이인 3을 곱한다)
			-> 5 * 3 = 15
			결과: 최대 직사각형은 15

			2-1. 9, 8, 7
			마지막 막대기 꺼내고 stack이 비어 있으면 모든 막대 길이를 포함하는 직사각형을 만들 수 있다
			stack (0, 9) / inputHeight (1, 8) -> 9 * 1 = 9
			stack (1, 8) / inputHeight (2, 7) -> 8 * 2 = 16
			나머지 stack (2, 7) -> 7 * 3 = 21
			결과: 21
			*/
			if (false == stack.Empty() && inputHeight < stack.Back().height) {
				do{
					//마지막 막대를 꺼낸다
					const Bar& lastBar = stack.Back();
					stack.PopBack();

					//마지막 막대가 어디까지 갈 수 있는지 찾는다.
					//스택은 오름차순 -> 스택에 아무것도 없다면 여태까지 내림차순이었다는 뜻
					//그러면 마지막 막대는 히스토그램의 처음부분까지 사각형을 연결할 수 있다.
					ll width = i;
					
					//만약 마지막 막대보다 짧은 막대가 있다면 스택에 저장되어 있을것이다.
					//마지막 막대 길이로는 짧은 막대 이상 이동할 수 없다.(최대 직사각형의 가로 길이가 됨)
					if (false == stack.Empty()) {
						width -= (stack.Back().idx + 1);
					}

					//구한 최대 직사각형 길이와 최댓값을 비교 후 저장
					maxSquare = std::max(maxSquare, lastBar.height * width);
				}
				//이번에 입력받은 막대보다 긴 막대들만 제거해야 오름차순이 가능함
				//-> 이번에 입력받은 막대보다 짧은 막대가 있을 경우 루프 중단
				while (false == stack.Empty() && inputHeight < stack.Back().height);
			}

			//입력받은 막대기를 stack에 넣어준다.
			stack.PushBack({ i, inputHeight });
		}

		//stack 잔여물들에 대한 계산
		while (false == stack.Empty()) {
			const Bar& lastBar = stack.Back();
			stack.PopBack();
			ll width = N;
			if (false == stack.Empty()) {
				width -= (stack.Back().idx + 1);
			}
			maxSquare = std::max(maxSquare, lastBar.height * width);
		}

		std::cout << maxSquare << '\n';
	}


	return 0;
}
