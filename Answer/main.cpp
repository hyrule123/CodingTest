#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

using namespace std;
int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

//https://www.slideshare.net/slideshow/baekjoon-online-judge-1019/52810015
int digit_count[10]{};

//135? 형태의 수, num = 135, digit_start = 2 -> 1350, 1351, ... 1359 -> 1, 3, 5가 9회 등장한다.
//digit_start가 2이므로 1의 자리 수는 카운트하지 않는다
void count(int num, int digit_level) {
	while (num > 0) {
		digit_count[num % 10] += digit_level;
		num /= 10;
	}
}

//핵심 아이디어
//10 ~ 39 -> 0~9가 3번 반복된다. -> 시작 자릿수와 끝 자릿수를 각각 0, 9로 맞춘뒤 계산 가능
//ex) 1 ~ 1234
//1. 1230 ~ 1234 계산: 일의 자리
//2. 120(0) ~ 122(9) 계산: 십의 자리
//3. 10(0) ~ 11(9) 계산: 백의 자리
//4. 0(0) ~ 0(9) 계산: 천의 자리

void count_ranged(int start, int end, int cur_digit) {
	//start를 0으로 맞춤(올리는동안의 숫자도 전부 반영)
	while (start % 10 != 0 && start <= end) {
		count(start, cur_digit);
		++start;
	}
	if (end < start) { return; }
	//마찬가지로 end도
	while (end % 10 != 9 && start <= end) {
		count(end, cur_digit);
		--end;
	}
	//ex. 1130부터 1249 까지는 124 - 113 + 1 회 반복. 
	//현재 자릿수만큼 더해준다.ex. (1130xx ~ 1249xx) == (1130 ~ 1249) * 100
	int num_count = (end / 10 - start / 10 + 1) * cur_digit;
	for (int i = 0; i < 10; ++i) {
		digit_count[i] += num_count;
	}

	count_ranged(start / 10, end / 10, cur_digit * 10);
}

void solve() {
	int N;  cin >> N;

	//재귀
	count_ranged(1, N, 1);
	
	for (int i : digit_count) {
		cout << i << ' ';
	}
}