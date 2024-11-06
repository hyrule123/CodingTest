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

#include <vector>
#include <string>

//15!를 저장하기 위해서는 8바이트 정수가 필요하다.
using ull = unsigned long long;

ull GCD(ull a, ull b) {
	ull remainder{};
	while (b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;
}

struct ret_val {
	ull mod, count;
};
struct mod_info {
	ull mod, len;
};

string num_str[16];

//dp[i][j]: i: 사용 현황 비트마스크, j: 나머지가 j
//dp 값: 나머지가 j였던 문자열 중, 나눠 떨어지는 문자열들의 갯수
ull N, K, _10_mod_K[51], dp[1ull << 16][101];
mod_info mods[16];


ull recursive(ull used_mask, ull last_mod) {
	ull& cur_mod_count = dp[used_mask][last_mod];

	//전부 붙였을 경우: 나머지가 0인지 확인한다.
	if (used_mask == (1ull << N) - 1ull) {
		return (ull)(bool)(last_mod % K == 0);
	}

	if (cur_mod_count == -1ull) {
		cur_mod_count = 0;

		//next: next string index
		for (ull next = 0; next < N; ++next) {
			if (used_mask & 1ull << next) { continue; }

			//문자열을 붙이고 난 후의 나머지를 계산한다.
			ull concat_mod =
				(last_mod * _10_mod_K[mods[next].len]) % K
				+ mods[next].mod;
			concat_mod %= K;

			//dp에 저장된, 해당 나머지를 가진 문자열 중 
			cur_mod_count += 
				recursive(used_mask | 1ull << next, concat_mod);
		}
		
	}

	return cur_mod_count;
}

//모든 경우의 수를 살펴봐야 하므로 완전탐색은 필수
//또한 숫자의 길이가 최대 50이므로, 바로 정수 타입에 대입도 불가능.
//쪼개야 쓸 수 있다.

void solve() {
	cin >> N;
	for (ull i = 0; i < N; ++i) {
		cin >> num_str[i];
	}
	cin >> K;

	_10_mod_K[0] = 1ull;
	for (ull i = 1ull; i <= 50; ++i) {
		_10_mod_K[i] = (_10_mod_K[i - 1ull] * (10 % K)) % K;
	}

	//DP setting
	//모든 숫자에 대한 mod와 길이를 저장한다.
	for (ull i = 0; i < N; ++i) {
		const string& s = num_str[i];
		mod_info& cur = mods[i];

		cur.len = (ull)s.size();
		for (ull j = 0; j < cur.len; ++j) {
			cur.mod += (((ull)(s[j] - '0') % K) * (_10_mod_K[cur.len - j - 1ull])) % K;
		}
	}

	memset(dp, -1, sizeof(dp));
	ull sum = recursive(0, 0);
	ull all_cases = 1ull;
	for (ull i = 1ull; i <= N; ++i) {
		all_cases *= i;
	}
	ull gcd = GCD(sum, all_cases);

	cout << sum / gcd << '/' << all_cases / gcd;

}