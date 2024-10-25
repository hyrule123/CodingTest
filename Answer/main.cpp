#include <string>
#include <vector>
#include <stack>
using namespace std;

int target_num, end_idx;
vector<int>* nums;

int recursive(int cur_idx, int sum) {
    int cur_num = (*nums)[cur_idx];
    if (cur_idx == end_idx) {
        return (bool)(sum + cur_num == target_num || sum - cur_num == target_num);
    }

    int ret = recursive(cur_idx + 1, sum + cur_num);
    ret += recursive(cur_idx + 1, sum - cur_num);

    return ret;
}

int solution(vector<int> numbers, int target) {
    nums = &numbers;
    target_num = target;
    end_idx = (int)numbers.size() - 1;

    int answer = recursive(0, 0);
    return answer;
}

int main() {
    auto ans = solution({ 1, 1, 1, 1, 1 }, 3);
    return 0;
}