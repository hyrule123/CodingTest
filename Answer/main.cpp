#include <string>
#include <vector>

using namespace std;
char ctoi(char c) {
    switch (c)
    {
    case 'A': return 1;
    case 'E': return 2;
    case 'I': return 3;
    case 'O': return 4;
    case 'U': return 5;
    }
    return 0;
}

struct word {
    word(const string& str) {
        for (size_t i = 0; i < str.size(); ++i) {
            c[i] = ctoi(str[i]);
            if (str[i]) {
                last_idx = (int)i;
            }
        }
    }

    word& operator ++() {
        if (last_idx < 4) {
            ++last_idx;
            c[last_idx] = 1;
        }
        else {
            while ((++c[last_idx]) == 6) {
                c[last_idx] = 0;

                if (last_idx == 0) {
                    break;
                }
                --last_idx;
            }
        }

        return *this;
    }

    bool operator != (const word& w) {
        for (int i = 0; i < 5; ++i) {
            if (c[i] != w.c[i]) {
                return true;
            }
        }

        return false;
    }


    int last_idx = 0;
    char c[8]{ 1, };
};

int solution(string _word) {
    int answer = 1;
    
    word w(_word);
    word A("A");

    while (A != w) {
        ++A;
        ++answer;
    }

    return answer;
}

int main() {
    auto ans = solution( "AAAE" );
    return 0;
}