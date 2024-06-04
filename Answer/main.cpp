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

//LIS 확인 시간복잡도 O(logN)인 버전
#include <vector>
int SearchLIS(std::vector<int>& _lis, int _u) {
	int start = 0;
	int end = (int)_lis.size();
	int mid = end / 2;
	while (start < end && 0 < mid) {
		if (_lis[mid - 1] < _u && _u <= _lis[mid]) { break; }
		if (_lis[mid] < _u) { start = mid; }
		else { end = mid; }
		mid = (start + end) / 2;
	}
	return mid;
}

//return val: 이번에 들어온 _u의 LIS 길이 - 1
int InsertLIS(std::vector<int>& _lis, int _u) {
	if (_lis.back() < _u) {
		_lis.push_back(_u);
		return (int)_lis.size() - 1;
	}
	int idx = SearchLIS(_lis, _u);
	_lis[idx] = _u;
	return idx;
}

int main() {
	READ_INPUT; WRITE_OUTPUT; USING_IOSTREAM;

	int N{}; std::cin >> N;

	struct inputLog { int val{}, maxSeqLen{ std::numeric_limits<int>::min() }; };
	//val: input값, maxSeqLen: 들어온 값까지 나올 수 있는 최대 배열의 길이
	std::vector<inputLog> inputs(N);
	std::vector<int> LIS; LIS.reserve(N);
	
	std::cin >> inputs[0].val;
	inputs[0].maxSeqLen = 0; //LIS에서의 인덱스 번호 겸 길이(길이는 +1)
	LIS.push_back(inputs[0].val);

	int maxLength = 0;
	int maxLengthIdx = 0;
	for (int i = 1; i < N; ++i) {
		std::cin >> inputs[i].val;

		//이거 하던 안하던 차이 없는데 있으면 중복값 반복 시 걸러낼 수 있으니까 그냥 하는게 좋을듯
		if (inputs[i].val == inputs[i - 1].val) { continue; }

		inputs[i].maxSeqLen = InsertLIS(LIS, inputs[i].val);

		//max값 갱신시 길이와 인덱스 번호를 기록
		if (maxLength < inputs[i].maxSeqLen) {
			maxLength = inputs[i].maxSeqLen;
			maxLengthIdx = i;
		}
	}

	std::cout << LIS.size() << '\n';

	//LIS배열 쓸모없어졌으므로 output으로 재사용
	std::vector<int>& outputs = LIS;
	outputs.clear();

	//기록된 max값 인덱스로부터 역순으로 내려오면서 마지막으로 LIS에 입력된 수를 출력한다.
	//ex) { 1 5 2 3 } 을 LIS에 넣으면 { 0,1/1,5/1,2/2,3 } -> 역순으로 내려오면 각 오름차순 수열이 만들어짐
	for (int i = maxLengthIdx; i >= 0 && maxLength >= 0; --i) {
		if (maxLength == inputs[i].maxSeqLen) {
			outputs.push_back(inputs[i].val);
			--maxLength;
		}
	}
	for (int i = (int)outputs.size() - 1; i >= 0; --i) { std::cout << outputs[i] << ' '; }

	return 0;
}
