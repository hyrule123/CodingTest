#include <vector>
#include <string>
using namespace std;

const int INF = (int)9e8;

void init(vector<string> arr, vector<int>& nums, vector<string>& ops) {
    // 숫자와 연산자로 나눠 저장
    for (int i = 0; i < arr.size(); i++) {
        if (i % 2 == 0) {
            nums.push_back(stoi(arr[i]));
        }
        else {
            ops.push_back(arr[i]);
        }
    }
}

int solution(vector<string> arr)
{

    int answer = -1;
    vector<int> nums;
    vector<string> ops;

    init(arr, nums, ops);

    vector<vector<int>> max_dp(nums.size(), vector<int>(nums.size()));
    vector<vector<int>> min_dp(nums.size(), vector<int>(nums.size()));

    //step: 길이
    for (int step = 0; step < nums.size(); step++) {
        //i번쨰 행
        for (int i = 0; i < nums.size() - step; i++) {
            //[i][j]: i번 숫자부터 j번 숫자까지 괄호쳤을경우 나오는 최대값
            int j = i + step;
            if (step == 0) {
                max_dp[i][j] = nums[i];
                min_dp[i][j] = nums[i];
            }
            else {
                max_dp[i][j] = -INF;
                min_dp[i][j] = INF;
                for (int k = i; k < j; k++) {
                    // dp(i,k) dp(k+1,j)
                    // 연산자 검사 ops[k]
                    if (ops[k] == "+") {
                        //max = max + max
                        max_dp[i][j] = max(max_dp[i][j], max_dp[i][k] + max_dp[k + 1][j]);
                        //min = min + min
                        min_dp[i][j] = min(min_dp[i][j], min_dp[i][k] + min_dp[k + 1][j]);
                    }
                    else {
                        //max = max - min
                        max_dp[i][j] = max(max_dp[i][j], max_dp[i][k] - min_dp[k + 1][j]);
                        //min = min - max
                        min_dp[i][j] = min(min_dp[i][j], min_dp[i][k] - max_dp[k + 1][j]);
                    }
                }
            }

        }
    }

    answer = max_dp[0][nums.size() - 1];
    return answer;
}
int main() {
    auto ans = solution({ "1", "-", "3", "+", "5", "-", "8" });
    return 0;
}