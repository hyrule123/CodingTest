#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> people, int limit) {
    int boat_count = 0;

    sort(people.begin(), people.end());
    
    int l = 0, r = (int)people.size() - 1;
    while (l <= r) {
        if (people[l] + people[r] <= limit) {
            ++l; --r;
        }
        //둘이 합해서 limit를 넘을 경우 무거운 승객을 혼자 태워 보낸다
        else {
            --r;
        }

        ++boat_count;
    }

    return boat_count;
}

int main() {
    auto ans = solution({70, 80, 50 }, 100);
    return 0;
}