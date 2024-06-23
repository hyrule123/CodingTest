#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
using ull = unsigned long long;
std::vector<ull> histogram;
struct hRect {
	ull maxHeight, start, end, square;

	void CompareAndUpdate(ull _idx, bool _isStart) {
		if (maxHeight < histogram[_idx]) {
			if (_isStart) { start = _idx; }
			else { end = _idx; }
			square = maxHeight * (end - start + 1);
		}
		else {
			ull newSquare = histogram[_idx] * (end - start + 1);
			if (newSquare < square) {
				if (_isStart) { start = _idx; }
				else { end = _idx; }
				square = newSquare;
				maxHeight = histogram[_idx];
			}
		}
	}
};

hRect Recursive(ull _start, ull _end) {
	if (_start >= _end) {
		hRect ret{};
		ret.maxHeight = histogram[_start];
		ret.start = _start;
		ret.end = _end;
		ret.square = ret.maxHeight;
		return ret;
	}
	
	ull midIdx = (_start + _end) / 2;
	enum e { left, right, mid, end };
	hRect rects[end]{};
	ull retIdx = left;
	rects[left] = Recursive(_start, midIdx);

	rects[right] = Recursive(midIdx + 1, _end);
	if (rects[retIdx].square < rects[right].square) { retIdx = right; }

	//Left와 Right를 붙일 수 있는 상태일 경우 두 분할 정사각형을 붙이고 
	if (rects[left].end + 1 == rects[right].start) {
		rects[mid].maxHeight = std::min(rects[left].maxHeight, rects[right].maxHeight);
		rects[mid].start = rects[left].start;
		rects[mid].end = rects[right].end;
		rects[mid].square = rects[mid].maxHeight * (rects[mid].end - rects[mid].start + 1);
	}
	//붙일 수 있는 상태가 아닐 경우 mid부터 양쪽으로 넓혀가며 탐색한다.
	else {
		rects[mid].start = midIdx;
		rects[mid].end = midIdx;
		rects[mid].maxHeight = histogram[midIdx];
		ull nextStart = rects[mid].start;
		ull nextEnd = rects[mid].end;
		while (true) {
			--nextStart;
			++nextEnd;

			if (nextStart == _start - 1 || nextEnd > _end) { break; }
			
			//왼쪽, 오른쪽 중 큰 막대를 먼저 선택한다.
			if (histogram[nextStart] > histogram[nextEnd]) {
				rects[mid].CompareAndUpdate(nextStart, true);
			}
			else {
				rects[mid].CompareAndUpdate(nextEnd, false);
			}
		}

		//남아있는 막대들에 대해서도 최대값 확인
		for (ull l = rects[mid].start; l != _start - 1; --l) {
			rects[mid].CompareAndUpdate(l, true);
		}
		for (ull r = rects[mid].end; r <= _end; ++r) {
			rects[mid].CompareAndUpdate(r, false);
		}
	}

	//최대값 비교 후 반환할 인덱스를 결정
	if (rects[retIdx].square < rects[mid].square) {
		retIdx = mid;
	}

	//반환값: 좌, 우 히스토그램을 합친 부분에서 가장 큰 직사각형 넓이
	return rects[retIdx];
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;
	
	while (true) {
		ull input; std::cin >> input;
		if (0 == input) { break; }

		histogram.resize(input);
		for (ull i = 0; i < input; ++i) {
			std::cin >> histogram[i];
		}

		hRect finalRect = Recursive( 0, histogram.size() - 1);

		std::cout << finalRect.maxHeight * (finalRect.end - finalRect.start + 1) << '\n';
	}

	return 0;
}
