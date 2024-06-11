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
using uint64 = std::uint64_t;

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;
	
	uint64 N, M; std::cin >> N >> M;
	std::vector<uint64> modsCount(M);
	uint64 mod0SeqCount = 0;

	uint64 prev; std::cin >> prev;
	prev %= M;
	if (prev == 0) { ++mod0SeqCount; }
	++modsCount[prev];
	
	for (uint64 i = 1; i < N; ++i) {
		uint64 cur; std::cin >> cur;

		//나머지를 기록
		cur += prev;
		cur %= M;

		//i까지의 전체 구간합이 0일 경우 합산
		if (cur == 0) {
			++mod0SeqCount;
		}

		++(modsCount[cur]);

		prev = cur;
	}

	//갯수는 1,000,000(10^6)개 까지 나올 수 있다 
	// -> 팩토리얼 하면 대략 10^6 * 10^6 = 10^12까지 나올수 있음
	// -> uint64를 사용해야 함(대략 1.844 * 10^19라고함)
	//부분 구간합 계산(부분합의 시작 - 1 인덱스 == 부분합일 겨우 나머지가 0)
	//-> 나머지가 r인 구간합 갯수 n 중 2개를 순서, 중복 없이 뽑는 경우 == nC2

	/*
	ex) 1 1 3
	-> sum = 1 2 5
	-> sumMod = 1 2 2
	-> 2-2 1개 -> 답 1
	*/

	for (uint64 i = 0; i < M; ++i) {
		if (2 <= modsCount[i]) {
			//nC2
			mod0SeqCount += (modsCount[i] * (modsCount[i] - 1)) / 2u;
		}
	}

	std::cout << mod0SeqCount;

	return 0;
}
