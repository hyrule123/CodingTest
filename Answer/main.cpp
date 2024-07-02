#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using uint = unsigned int;

std::vector<uint> dists;
std::vector<uint> temp;
void MergeSort(uint _start, uint _end) {
	if (_start >= _end) { return; }

	uint mid = (_start + _end) / 2;
	MergeSort(_start, mid);
	MergeSort(mid + 1, _end);

	uint l = _start;
	uint r = mid + 1;
	uint i = _start;
	while (l <= mid && r <= _end) {
		if (dists[l] < dists[r]) {
			temp[i] = dists[l]; ++l;
		}
		else {
			temp[i] = dists[r]; ++r;
		}
		++i;
	}
	for (; l <= mid; ++l) {
		temp[i] = dists[l];
		++i;
	}
	for (; r <= _end; ++r) {
		temp[i] = dists[r];
		++i;
	}

	memcpy(dists.data() + _start, temp.data() + _start, sizeof(uint) * (_end - _start + 1));
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	uint N, C; std::cin >> N >> C;
	dists.resize(N); temp.resize(N);
	for (uint i = 0; i < N; ++i) {
		std::cin >> dists[i];
	}
	MergeSort(0, (uint)dists.size() - 1);

	//최대거리 구하고
	uint minDist = 1, maxDist = dists.back() - dists.front() + 1;

	//배열 안의 값들을 두 집 사이의 거리로 변경
	for (uint i = 0; i < N - 1; ++i) {
		dists[i] = dists[i + 1] - dists[i];
	}
	--N; dists.resize(N);
	
	while (minDist + 1 < maxDist) {
		uint mid = (minDist + maxDist) / 2;

		uint count = 1;	//첫 집에는 무조건 공유기를 설치해야 최대거리를 뽑을수 있다
		uint sum = 0;

		for (uint i = 0; i < N; ++i) {
			sum += dists[i];
			//이번 루프에서 요구하는 거리 이상이 되면 sum을 초기화하고 count를 올려준다(공유기를 설치한다)
			if (mid <= sum) {
				sum = 0;
				++count;
			}
		}

		if (C <= count) {
			minDist = mid;
		}
		else {
			maxDist = mid;
		}
	}
	std::cout << minDist;

	return 0;
}