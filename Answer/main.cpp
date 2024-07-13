#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1725 (히스토그램)
*/
#include <array>
struct bar { int height, pos; };
constexpr int arrSize = 100000;
struct Stack {
	std::array<bar, arrSize> cont{};
	int size = 0;

	bool Empty() { return size == 0; }
	int Size() { return size; }
	bar& Back() { return cont[size - 1]; }
	void Push(bar b) { cont[size] = b; ++size; }
	void Pop() { --size; }

} histogram;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N; std::cin >> N;
	int maxSquare = 0;
	for (int i = 0; i < N; ++i) {
		bar b; std::cin >> b.height;
		b.pos = i;

		//이번 막대가 스택의 마지막 막대보다 짧을 경우 
		//스택에서 이번 막대보다 짧은 막대가 나올때까지 하나씩 꺼내서 가로길이에 합산
		//스택에 2 3 4 있고 1이 들어왔으면 -> max(4 * 1, 3 * 2, 2 * 3)
		while (false == histogram.Empty() && b.height < histogram.Back().height) {
			bar& lastBar = histogram.Back();
			histogram.Pop();
			int width = i;

			//비어있으면 히스토그램의 끝까지 이동가능(ex. 3 2 1에서 1의 경우를 생각해보자)
			if (false == histogram.Empty()) {
				width -= (histogram.Back().pos + 1);
			}

			maxSquare = std::max(maxSquare, lastBar.height * width);
		}

		histogram.Push(b);
	}

	//나머지 막대들에 대한 계산
	while (false == histogram.Empty()) {
		bar& lastBar = histogram.Back();
		histogram.Pop();
		int width = N;

		//비어있으면 히스토그램의 끝까지 이동가능(ex. 3 2 1에서 1의 경우를 생각해보자)
		if (false == histogram.Empty()) {
			width -= histogram.Back().pos + 1;
		}

		maxSquare = std::max(maxSquare, lastBar.height * width);
	}

	std::cout << maxSquare;

	return 0;
}