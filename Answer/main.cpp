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

#include <string>
#include <vector>
constexpr int max_len = 1'000'001;
int lenT, lenP;
char T[max_len], P[max_len];
int Pi[max_len];	//KMP 알고리즘의 pi 배열: P[i]까지 문자열에서 찾을 수 있는 prefix == suffix 가장 긴 길이)

void calc_last_match() {
	int prefix = 0;	//previous longest prefix len
	for (int suffix = 1; suffix < lenP; ++suffix) {

		//suffix 문자가 prefix 문자와 일치하지 않으면 Pi 배열을 참조하여 줄여나간다.
		//prefix = Pi[prefix - 1] 인 이유
		//AAAB'AAA(3) -> AAAB'AAAA
		//지난 prefix길이: 3(AAA)
		//문자열 추가, 패턴 일치 확인 -> AAAB != AAAA(불일치)
		//지난 prefix 중 다음으로 긴 걸 가져온다: Pi[3 - 1] -> "AAA" 문자열에서 일치하는 prefix와 suffix -> "AA"(2)
		while (0 < prefix && P[prefix] != P[suffix]) {
			prefix = Pi[prefix - 1];
		}

		if (P[suffix] == P[prefix]) {
			Pi[suffix] = ++prefix;
		}
		//else Pi[suffix] = 0
	}
}

void KMP() {
	int matches = 0;
	vector<int> match_idx{};

	int j = 0;
	for (int i = 0; i < lenT; ++i) {
		//패턴 불일 치 시 그 다음으로 긴 prefix를 가져온다.
		while (0 < j && T[i] != P[j]) {
			j = Pi[j - 1];
		}

		//문자 일치 시
		if (T[i] == P[j]) {
			//전체 패턴 일치 시 답에 추가하고 부분일치 인덱스를 찾아 다시 이동
			if (lenP - 1 == j) {
				++matches;
				match_idx.push_back(i - lenP + 2);	//답은 1부터 시작
				j = Pi[j];
			}
			else {
				++j;
			}
		}
	}

	cout << matches << '\n';
	for (int idx : match_idx) {
		cout << idx << ' ';
	}
}

void solve() {
	cin.getline(T, max_len);
	lenT = (int)strlen(T);
	cin.getline(P, max_len);
	lenP = (int)strlen(P);
	calc_last_match();
	KMP();
}