#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<int> solution(int brown, int yellow) {
    vector<int> answer;

    //근의 공식
    int a = 1;
    int b = -(brown + 4) / 2;
    int c = brown + yellow;
    int sqpart = (int)sqrt(b * b - 4 * a * c);
    int y1 = (-b + sqpart) / 2 * a;
    int y2 = (-b - sqpart) / 2 * a;

    answer.push_back(max(y1, y2));
    answer.push_back(min(y1, y2));

    return answer;
}

int main() {
    auto ans = solution(24, 24);

    return 0;
}