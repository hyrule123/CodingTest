#include <string>
#include <vector>
using namespace std;

int clamp(int i, int min, int max) {
    if (i < min) { return min; }
    if (max <= i) { return max - 1; }

    return i;
}

int solution(vector<vector<int>> triangle) {
    int answer = 0;

    //역으로 생각해서 윗쪽의 좌/우 값중 큰걸 취사선택
    for (int i = 1; i < (int)triangle.size(); ++i) {
        for (int j = 0; j < (int)triangle[i].size(); ++j) {
            int left = clamp(j - 1, 0, (int)triangle[i - 1].size());
            int right = clamp(j, 0, (int)triangle[i - 1].size());
            //부모: j-1, j 중 하나
            triangle[i][j] += max(triangle[i - 1][left], triangle[i - 1][right]);
            answer = max(answer, triangle[i][j]);
        }
    }

    return answer;
}

int main() {
    auto ans = solution({{7}, {3, 8}, {8, 1, 0}, {2, 7, 4, 4}, {4, 5, 2, 6, 5}} );
    return 0;
}