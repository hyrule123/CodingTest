#include <string>
#include <vector>
#include <queue>
using namespace std;

string solution(string number, int k) {
    string answer = "";
    size_t ans_size = number.size() - k;
    answer.resize(ans_size);

    //number에서 탐색중인 인덱스 자리
    size_t cursor = 0;

    //한글자씩 채워나간다.
    for (size_t i = 0; i < ans_size; ++i) {
        size_t max_idx = cursor;
        
        //건너뛸 수 있는 최대 자리는 i + k개(현재 위치로부터 K개)
        //시작 인덱스는 마지막 커서 자리 + 1
        for (size_t j = cursor + 1; j <= i + k; ++j) {
            if (number[max_idx] < number[j]) {
                max_idx = j;
            }
        }

        cursor = max_idx + 1;
        answer[i] = number[max_idx];
    }

    return answer;
}
int main() {
    auto ans = solution("179252841", 6);
    return 0;
}