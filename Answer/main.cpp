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

#include <vector>
#include <string>
int LCSMax = 0;
std::string a, b;
int Recursive(size_t _i, size_t _j, int _prev) {
	if (_i >= a.size() || _j >= b.size()) {
		return _prev;
	}

	if (a[_i] == b[_j]) {
		return Recursive(_i + 1, _j + 1, _prev + 1);
	}

	int max = std::max(Recursive(_i + 1, _j, _prev), Recursive(_i, _j + 1, _prev));
	return max;
}

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	 std::cin >> a >> b;
	for (size_t i = 0; i < a.size(); ++i) {
		if (LCSMax + (int)i >= a.size()) { 
			break; 
		}

		for (size_t j = 0; j < b.size(); ++j) {
			if (LCSMax + (int)j >= b.size()) { 
				break; 
			}

			if (a[i] == b[j]) {
				LCSMax = std::max(LCSMax, Recursive(i + 1, j + 1, 1));
			}
		}
	}
	std::cout << LCSMax;

	return 0;
}
