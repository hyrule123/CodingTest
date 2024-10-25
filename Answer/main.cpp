#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0;

    //진출 지점 기준으로 정렬하고
    sort(routes.begin(), routes.end(),
        [](const vector<int>& a, const vector<int>& b)->bool
        {
            return a[1] < b[1];
        }
        );

    //진입 지점 기준으로 비교
    int last_cam_pos = -30001;
    for (size_t i = 0; i < routes.size(); ++i) {
        //마지막으로 설치한 카메라 위치가 진입지점보다 뒤쪽일 경우 진출 지점쪽에 새로 설치해야 한다
        if (last_cam_pos < routes[i][0]) {
            last_cam_pos = routes[i][1];
            ++answer;
        }
    }

    return answer;
}
int main() {
    auto ans = solution({ {-20, -15}, {-14, -5}, {-18, -13}, {-5, -3} });
    return 0;
}