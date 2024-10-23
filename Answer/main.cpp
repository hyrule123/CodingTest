#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
bool is_prime(int n) {
    if (n <= 1) { return false; }
    else if (n <= 3) { return true; }
    
    if (n % 2 == 0 || n % 3 == 0) { return false; }

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

int solution(string numbers) {
    int answer = 0;

    unordered_map<int, bool> found;

    sort(numbers.begin(), numbers.end());
    for (char c : numbers) {
        int i = (int)(c - '0');
        if (false == found[i]) {
            found[i] = true;

            if (is_prime(c - '0')) {
                ++answer;
            }
        }
    }

    do
    {
        for (size_t i = 2; i <= numbers.size(); ++i) {
            string_view numstr(numbers.data(), i);
            
            int num = 0;
            for (char c : numstr) {
                num *= 10;
                num += (int)(c - '0');
            }
            
            if (false == found[num]) {
                found[num] = true;

                if (is_prime(num)) {
                    ++answer;
                }
            }
        }

    } while (next_permutation(numbers.begin(), numbers.end()));

    return answer;
}

int main() {
    auto ans = solution("011");

    return 0;
}