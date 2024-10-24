#include <string>
#include <vector>
using namespace std;

constexpr int pow(int base, int exp) {
    int ret = 1;
    for (int i = 0; i < exp; ++i) {
        ret *= base;
    }
    return ret;
}

//"A" 에서 "E"로 가는 경우의 수 ("A", "AA", ... "AUUUU", "E"): 5^4 + 5^3 + ... +  5^0
//"AA"에서 "AE"로 가는 경우의 수 5^3 + 5^2 + 5^1 + 5^0 -> "A"->"E"로 가는 경우의 수에서 5를 나눠주면됨
constexpr int a_to_e = 
pow(5, 4) + 
pow(5, 3) + 
pow(5, 2) + 
pow(5, 1) + 
pow(5, 0);

int solution(string word) {
    int answer = 0;

    const string_view chars = "AEIOU";

    //가장 앞자리수부터 몇번쨰인지 계산해서 더해준다
    for (int i = 0, c = 1; i < (int)word.size(); ++i, c *= 5) {
        answer += chars.find(word[i]) * a_to_e / c;
    }

    return answer;
}

int main() {
    auto ans = solution( "AAAE" );
    return 0;
}