#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif

#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	int input; std::cin >> input;
	int sum = input;

	//음수 기호 첫 발견 이후로 다음 음수까지 전부 괄호치면 그게 최솟값이 되므로
	bool negativeFound = false;
	while (std::cin >> input) {
		if (input < 0) { 
			negativeFound = true;
			input = -input;
		}

		if (negativeFound) {
			sum -= input;
		}
		else {
			sum += input;
		}
	}
	std::cout << sum;

	return 0;
}
