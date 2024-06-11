#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif
#define USING_IOSTREAM std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false)
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <array>
std::array<std::array<int, 28>, 200000> usages;

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;
	
	std::array<int, 28> useCount{};
	int i = 0;
	while (true) {
		int c = std::cin.get();
		if (c == '\n') { break; }

		c -= 'a';
		++(useCount[c]);
		usages[i] = useCount;

		++i;
	}
	
	int N; std::cin >> N;
	for (int i = 0; i < N; ++i) {
		char c; int start, end; std::cin >> c >> start >> end;
		c -= 'a';

		if (start == 0) {
			std::cout << usages[end][c] << '\n';
		}
		else {
			std::cout << usages[end][c] - usages[start - 1][c] << '\n';
		}
	}

	return 0;
}
