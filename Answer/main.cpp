#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <bitset>
std::bitset<15001> combi;
int ABS(int _i) { if (_i < 0) { _i = -_i; } return _i; }

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int nWeight, weights[30]{}, weightMax = 0; std::cin >> nWeight;
	combi[0] = true;
	for (int i = 0; i < nWeight; ++i) {
		std::cin >> weights[i];
		weightMax += weights[i];

		//역순으로 하지 않으면, 1g에 3g 추를 추가한다고 할때
		//0, 1, 4(1+3), 7(4+3), 10(7+3)... 중복 true가 생성됨.
		for (int j = weightMax; j >= 0; --j) {
			if (combi[j]) {
				//기존 조합 + 오른쪽 저울에 추를 추가
				combi[j + weights[i]] = true;
			}
		}
		
		//위와 마찬가지 이유로 순차적으로 해야 함.
		for (int j = 0; j <= weightMax; ++j) {
			if (combi[j]) {
				//기존 조합 + 왼쪽 저울에 추를 추가
				combi[ABS(j - weights[i])] = true;
			}
		}
	}

	int nOrbs; std::cin >> nOrbs;
	while (nOrbs--) {
		int orbWeight; std::cin >> orbWeight;
		if (combi[orbWeight]) {
			std::cout << "Y ";
		}
		else {
			std::cout << "N ";
		}
	}

	return 0;
}