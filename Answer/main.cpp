#include <string>
#include <vector>
using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;

    vector<int> states((size_t)(n + 1), 1);

    //체육복 여벌 있으면 +1
    for (int i : reserve) {
        ++(states[i]);
    }
    //잃어버렸으면 -1(여벌 있는데 잃어버렸을수도 있음)
    for (int i : lost) {
        --(states[i]);
    }
    for (int i = 1; i <= n; ++i) {
        //체육복 없으면
        if (states[i] == 0) {
            //일단 앞에서 빌려본다(앞은 이미 지나갔으므로)
            if (states[i - 1] == 2) {
                ++(states[i]);
                --(states[i - 1]);
                ++answer;   //빌렸으면 +1
            }
            //앞에 없으면 뒤에서 빌려본다
            else if (states[i + 1] == 2) {
                ++(states[i]);
                --(states[i + 1]);
                ++answer;
            }

        }
        //있으면 +1
        else {
            ++answer;
        }
    }

    return answer;
}

int main() {
    auto ans = solution(5, {2, 4}, {1, 2, 3, 5});
    return 0;
}