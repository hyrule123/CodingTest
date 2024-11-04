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
struct tree_info {
	int num_holes{};
	vector<int> holes{};
};
constexpr int NONE = -1;
int N, K;
int dp[101][21];
vector<int> trees[101];

//return: T 사용 횟수
//아이디어: 이전 인덱스에서 현재 인덱스로 이동했을 때의 값을 가져온다
void solve_dp() {
	dp[0][1] = K;
	for (int tree_idx = 1; tree_idx <= N; ++tree_idx) {
		for (int cur_height : trees[tree_idx]) {
			int& cur_dp = dp[tree_idx][cur_height];

			//O
			cur_dp = max(cur_dp, dp[tree_idx - 1][cur_height]);

			//A
			if (1 <= cur_height - 1) {
				cur_dp = max(cur_dp, dp[tree_idx - 1][cur_height - 1]);
			}
			
			//B
			if (cur_height < 20) {
				//*2를 해서 올라오는 것이므로 짝수일때만 가능
				if (cur_height % 2 == 0) {
					cur_dp = max(cur_dp, dp[tree_idx - 1][cur_height / 2]);
				}
			}
			//cur_height == 20일 떄
			else {
				//20은 O에서, 19는 A에서 처리했음
				for (int j = 10; j <= 18; ++j) {
					cur_dp = max(cur_dp, dp[tree_idx - 1][j]);
				}
			}

			//C
			if (cur_height + 1 <= 20) {
				cur_dp = max(cur_dp, dp[tree_idx - 1][cur_height + 1]);
			}

			//T: 이전 나무 구멍의 값 - 1(T를 1회 사용했으므로)
			for (int prev_height : trees[tree_idx - 1]) {
				cur_dp = max(cur_dp, dp[tree_idx - 1][prev_height] - 1);
			}
		}
	}
}


void solve() {
	memset(dp, NONE, sizeof(int) * 101 * 21);

	cin >> N >> K;
	
	trees[0].push_back(1);
	for (int i = 1; i <= N; ++i) {
		int M; cin >> M;
		trees[i].resize(M);
		for (int j = 0; j < M; ++j) {
			cin >> trees[i][j];
		}
	}

	
	solve_dp();
	int result = -1;
	for (int remain : dp[N]) {
		result = max(result, remain);
	}

	//사용횟수가 남아있을 경우 K - 사용횟수 출력, 아닐 시 -1 출력
	cout << (0 <= result ? K - result : -1);
}