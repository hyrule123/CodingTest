#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
#include <limits>

#include <vector>
class DigitCounter
{
public:
    DigitCounter(std::vector<char>& _defaultDigit) : digits{} { digits.swap(_defaultDigit); digits.reserve(64); };
    ~DigitCounter() {};

    inline void operator ++() 
    {
        Add1Recursive(0);
    }

    inline std::uint64_t GetNumber()
    {
        std::uint64_t ret{};
        std::uint64_t digitExponent = 1;
        for (size_t i = 0; i < digits.size(); ++i)
        {
            ret += digits[i] * digitExponent;
            digitExponent *= 10;
        }
        return ret;
    }

    inline bool Is666()
    {
        bool ret = false;

        if (2 < digits.size())
        {
            int serialCount{};
            for (size_t i = 0; i < digits.size(); ++i)
            {
                if (6 == digits[i])
                {
                    ++serialCount;
                }
                else
                {
                    serialCount = 0;
                }

                if (3 == serialCount)
                {
                    ret = true;
                    break;
                }
            }
        }

        return ret;
    }

private:
    void Add1Recursive(size_t _idx)
    {
        if (_idx >= digits.size())
        {
            digits.push_back(0);
        }

        char digit = ++digits[_idx];
        if (digit >= 10)
        {
            digits[_idx] = 0;
            Add1Recursive(++_idx);
        }
    }
    std::vector<char> digits;
};

int main()
{
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    int N{};
    std::cin >> N;

    //거꾸로 넣어줘야함
    std::vector<char> digits{ 5, 6, 6 };
    DigitCounter checker{ digits };
    
    int _666Count{};
    while (true)
    {
        ++checker;
        if (checker.Is666())
        {
            ++_666Count;

            if (N == _666Count)
            {
                std::cout << checker.GetNumber();
                return 0;
            }
        }
    }
    return 0;
}
