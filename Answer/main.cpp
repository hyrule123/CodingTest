#include <string>
#include <vector>
using namespace std;
constexpr int AB_size = (int)('Z' - 'A' + 1);

int solution(string name) {
    const int str_size = (int)name.size();

    /*
    좌우 확인 로직
    1. name[i]에서 시작해서, 오른쪽으로 가장 가까운 'A'가 아닌 문자열을 찾는다.
    2. 이 문자의 위치를 D라고 할 때
    3. 다음 3가지 경우의 수 중 제일 작은 수를 구한다.
        1. D와 상관 없이 그냥 0에서 끝까지 순회하는 경우: (단어길이) - 1
        2. 0에서 i까지 오른쪽으로 이동했다가, 다시 왼쪽으로 돌아서 D까지 가는 경우
            "BAABAAAAAAAAAABAAAA"
        3. 0에서 i까지 왼쪽으로 이동했다가, 다시 오른쪽으로 돌아서 D까지 가는 경우
            "BAAAABBAAAAAAABA"
    */
    int updown_min = 0;
    int leftright_min = str_size - 1;//3-1 경우의 수
    for (int i = 0; i < str_size; ++i) {
        int updown = (int)(name[i] - 'A');

        //상하 확인
        if (name[i] != 'A') {
            updown_min += min(updown, AB_size - updown);
        }

        int idx = i + 1;
        //다음 A가 아닌 문자 위치 확인.
        while (idx < str_size && name[idx] == 'A') {
            ++idx;
        }
        
        //3-2 경우의 수
        leftright_min = min(leftright_min, i * 2 + (str_size - idx));

        //3-3 경우의 수
        leftright_min = min(leftright_min, (str_size - idx) * 2 + i);
    }

    return updown_min + leftright_min;
}
int main() {
    auto ans = solution("JAN");
    return 0;
}