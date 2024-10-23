#include <string>
#include <vector>
#include <set>
using namespace std;

set<int> dpq;
void insert(int i) {
    dpq.insert(i);
}

void pop_max() {
    if (dpq.empty()) { return; }
    dpq.erase(--(dpq.end()));
}

void pop_min() {
    if (dpq.empty()) { return; }
    dpq.erase(dpq.begin());
}

void interpret(const std::string& str) {
    if (str[0] == 'I') {
        std::string_view numpart(str.data() + 2, str.size() - 2);
        int num = 0; 
        bool is_neg = numpart[0] == '-';
        for (size_t i = is_neg ? 1 : 0; i < numpart.size(); ++i) {
            num *= 10;
            num += (int)(numpart[i] - '0');
        }
        if (is_neg) {
            num *= -1;
        }
        insert(num);
    }
    else if (str == "D -1") {
        pop_min();
    }
    else if (str == "D 1") {
        pop_max();
    }
}

vector<int> solution(vector<string> operations) {
    vector<int> answer(2);

    for (const string& str : operations) {
        interpret(str);
    }

    if (false == dpq.empty()) {
        answer[0] = *(--(dpq.end()));
        answer[1] = *(dpq.begin());
    }

    return answer;
}

int main() {

    auto ans = solution({ "I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333" });

    return 0;
}