#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

//dp[i]: N을 i번 사용했을때 결과 모음
vector<unordered_set<int>> dp;
int make_NN_N(int N, int digits) {
    int ret = N;

    for (int i = 1; i < digits; ++i) {
        ret *= 10;
        ret += N;
    }

    return ret;
}

int solution(int N, int number) {
    dp.resize(9);
    
    if (N == number) { return 1; }

    //5를 한번써서 만들수있는건 N
    dp[1].insert(N);

    //최솟값이 8 이하일 경우까지만 계산(문제 조건)
    for (int digits = 2; digits <= 8; ++digits) {

        dp[digits].insert(make_NN_N(N, digits));

        //ex. 3자리수일때: NNN, 1/2, 2/1
        for (int i = 1; i < digits; ++i) {
            for (int left : dp[i]) {
                for (int right : dp[digits - i]) {
                    dp[digits].insert(left + right);
                    dp[digits].insert(left * right);
                    
                    //0은 안됨
                    if (0 < left / right) {
                        dp[digits].insert(left / right);
                    }

                    //음수는 안됨
                    if (0 < left - right) {
                        dp[digits].insert(left - right);
                    }
                }
            }
        }

        if (dp[digits].find(number) != dp[digits].end()) {
            return digits;
        }
    }

    return -1;
}
int main() {
    auto ans = solution(5, 12);
    return 0;
}