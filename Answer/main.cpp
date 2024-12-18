#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;

	solve();
	return 0;
}

/*
백준 2805 (나무 자르기) [복습][이분탐색][매개변수 탐색]
https://m42-orion.tistory.com/70
1. 결정 문제로 풀면 쉽게 문제를 풀 수 있을 때
2-1. 어떤 시점까지는 조건을 만족하지만, 그 후로는 조건을 만족하지 않는 경우. 조건을 만족하는 최대값 찾기
2-2. 어떤 시점까지는 조건을 만족하지 않지만, 그 후로는 조건을 만족하는 경우. 조건을 만족하는 최소값 찾기

* 주요 포인트
1. 반복문 뒤쪽의 start, end 재설정 위치를 어떻게 하느냐에 따라 최소값, 최대값에 근접하는 값을 뽑아낼 수 있음
현재는 필요한 나무 길이를 충족시키는 '최대' 톱의 높이를 찾아야 하므로
start가 올라갈 때 값을 갱신시킨다면 근접한 값을 찾을 수 있다

2. 최소 충족 조건인 M은 최대 20억의 값을 가질 수 있다
만약 현재 15억의 나무를 확보해놓은 상태에서 길이 10억인 나무를 자른다면
int 타입에서는 오버플로우가 발생하므로 최소 uint는 써줘야 한다.
*/
using uint = unsigned int;
uint N, M, trees[1'000'000];

void solve() {
	cin >> N >> M;

	uint end = 0;
	for (uint i = 0; i < N; ++i) {
		cin >> trees[i];
		if (end < trees[i]) {
			end = trees[i];
		}
	}

	//톱의 최대 높이는 나무 최대 높이 -1
	--end;
	uint start = 0, answer = 0;
	while (start <= end) {

		uint height = (start + end) / 2;

		uint sum = 0;
		for (uint i = 0; i < N; ++i) {
			if (height < trees[i]) {
				sum = sum + (trees[i] - height);

				//이미 필요한 양을 넘어섰다면 break
				if (M < sum) {
					break;
				}
			}
		}

		if (sum < M) {
			end = height - 1;
		}
		else {
			answer = height;
			start = height + 1;
		}
	}

	cout << answer;
}