#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;
constexpr int maxsize = 10000000;
bitset<maxsize> is_prime;
void erastothenes() {
    is_prime.flip();
    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i < maxsize; ++i) {
        if (is_prime[i]) {
            for (int j = i * 2; j < maxsize; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

int solution(string numbers) {
    int answer = 0;

    erastothenes();

    sort(numbers.begin(), numbers.end());
    for (char c : numbers) {
        if (is_prime[c - '0']) {
            is_prime[c - '0'] = false;
            ++answer;
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
            
            if (is_prime[num]) {
                is_prime[num] = false;
                ++answer;
            }
        }

    } while (next_permutation(numbers.begin(), numbers.end()));

    return answer;
}

int main() {
    auto ans = solution("011");

    return 0;
}