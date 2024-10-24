#include <string>
#include <vector>
#include <cmath>
#include <bitset>
using namespace std;

int node_num;
bitset<101> nodes[101];

int dps(int node, int parent) {
    int count = 1;
    for (int i = 1; i <= node_num; ++i) {
        if (nodes[node][i] && i != parent) {
            count += dps(i, node);
        }
    }
    return count;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = (int)1e9;

    node_num = n;

    //bitset에 집어넣는다
    for (const vector<int>& wire : wires) {
        nodes[wire[0]][wire[1]] = true;
        nodes[wire[1]][wire[0]] = true;
    }

    for (size_t i = 0; i < wires.size(); ++i) {
        //확인하려는 전력망끼리 연결을 끊고
        nodes[wires[i][0]][wires[i][1]] = false;
        nodes[wires[i][1]][wires[i][0]] = false;

        //끊은 전신주를 루트노드로 해서 연결된 전신주 갯수 계산
        int left_count = dps(wires[i][0], 0);
        int right_count = n - left_count;

        //차이가 제일 적은 값을 대입
        answer = min(answer, abs(left_count - right_count));

        //다시 연결
        nodes[wires[i][0]][wires[i][1]] = true;
        nodes[wires[i][1]][wires[i][0]] = true;
    }

    return answer;
}

int main() {
    auto ans = solution(9, { {4, 7}, {1, 3}, {2, 3}, {3, 4}, {4, 5}, {4, 6}, {7, 8}, {7, 9}} );
    return 0;
}