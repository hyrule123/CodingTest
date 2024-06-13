#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif

#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
struct pair { 
	int start, end; 
	bool operator > (pair& _other) {
		if (end == _other.end) {
			return start < _other.start;
		}
		return end < _other.end;
	}
};

void MergeSort(std::vector<pair>& _vec, std::vector<pair>& _temp, size_t _start, size_t _end) {
	if (_start >= _end) { return; }

	size_t mid = (_start + _end) / 2;
	MergeSort(_vec, _temp, _start, mid);
	MergeSort(_vec, _temp, mid + 1, _end);

	size_t i = _start;
	size_t tempIdx = _start;
	size_t j = mid + 1;
	
	while (i <= mid && j <= _end) {
		if (_vec[i] > _vec[j]) {
			_temp[tempIdx] = _vec[i];
			++i; ++tempIdx;
		}
		else {
			_temp[tempIdx] = _vec[j];
			++j; ++tempIdx;
		}
	}

	for (; i <= mid; ++i, ++tempIdx) {
		_temp[tempIdx] = _vec[i];
	}
	for (; j <= _end; ++j, ++tempIdx) {
		_temp[tempIdx] = _vec[j];
	}

	memcpy(&(_vec[_start]), &(_temp[_start]), sizeof(pair) * (_end + 1 - _start));
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	READ_INPUT; WRITE_OUTPUT;

	int N; std::cin >> N;
	std::vector<pair> pairs(N);
	for (int i = 0; i < N; ++i) {
		std::cin >> pairs[i].start >> pairs[i].end;
	}
	std::vector<pair> temp(N);
	MergeSort(pairs, temp, 0, pairs.size() - 1);

	int count = 1;
	int lastMeeting = 0;
	for (int j = 1; j < N; ++j) {
		if (pairs[j].start >= pairs[lastMeeting].end) {
			++count;
			lastMeeting = j;
		}
	}

	std::cout << count;

	return 0;
}
