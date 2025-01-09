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
백준 5391 (Top 2000) [DP]
DP[i]: i번 노래까지 재생했을 경우 발생하는 penalty의 최소값
노래 N개에 대해서 정답은 DP[N]에 저장된다.
*/
#include <vector>

int calculate_penalty(int song_length, int block_size, int penalty_short, int penalty_long) {
    int diff = song_length - block_size;
    return (0 <= diff ? diff * penalty_long : -diff * penalty_short);
}

void solve() {
    int T;
    cin >> T;

    while (T--) {
        int num_song, block_size, penalty_short, penalty_long;
        cin >> num_song >> block_size >> penalty_long >> penalty_short;

        vector<int> partsum(num_song + 1);
        for (int i = 1; i <= num_song; ++i) {
            int input; cin >> input;;
            partsum[i] = partsum[i - 1] + input;
        }

        vector<int> dp(num_song + 1, numeric_limits<int>::max());
        dp[0] = 0;
        for (int i = 1; i <= num_song; ++i) {
            //한 블럭에 전부 쑤셔넣은 경우를 기본 패널티로 계산(최대값)
            dp[i] = calculate_penalty(partsum[i], block_size, penalty_short, penalty_long);

            //j: 구간합의 시작 부분, 즉 0 ~ j - 1, j ~ i 구간으로 분리
            //dp[j - 1] + {j ~ i 구간 음악 재생 시 발생하는 패널티} 의 최소값을 구한다
            for (int j = i; j >= 1; --j) {
                int song_length = partsum[i] - partsum[j - 1];

                dp[i] = min(dp[i], dp[j - 1] + calculate_penalty(song_length, block_size, penalty_short, penalty_long));

                //블록 사이즈를 넘어섰다면 중단
                if (block_size < song_length) {
                    break;
                }
            }
        }

        cout << dp[num_song] << '\n';
    }

}