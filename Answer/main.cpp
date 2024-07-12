#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
/*
백준 9935 (문자열 폭발)
*/
char input[1'000'001];
char bomb[37];
struct Stack {
	char cont[1'000'001]{};
	int size = 0;

	bool Empty() { return size == 0; }
	int Size() { return size; }
	void Push(char _c) { cont[size] = _c; ++size; }
	char Back() { return cont[size - 1]; }
	void Pop(int how = 1) { size -= how; }
};
Stack stack;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> input >> bomb;
	int inputLen = (int)strlen(input), bombLen = (int)strlen(bomb);
	char bombBack = bomb[bombLen - 1];

	for (int i = 0; i < inputLen; ++i) {
		stack.Push(input[i]);

		//한글자씩 확인
		if (bombBack == stack.Back() && bombLen <= stack.Size()) {
			bool same = true;
			for (int c = 1; c <= bombLen; ++c) {
				if (stack.cont[stack.Size() - c] != bomb[bombLen - c]) {
					same = false;
					break;
				}
			}

			//Bomb와 동일한 문자열일 경우 Bomb에 해당하는 문자열을 제거
			if (same) {
				stack.Pop(bombLen);
			}
		}
	}
	if (stack.Empty()) {
		std::cout << "FRULA";
	}
	else {
		stack.cont[stack.Size()] = '\0';
		std::cout << stack.cont;
	}

	return 0;
}