//basic babylonian algorithm
#include <cmath>
double SQRT(double _num) {
    if (_num <= 1) { return _num; }

    double a = _num / 2.0;
    constexpr double precision = 0.000001;
    while (std::abs(a * a - _num) > precision) {
        a = (a + _num / a) / 2.0;
    }

    return a;
}

//from geeksforgeeks
float squareRoot(float n)
{
    /*We are using n itself as initial approximation
      This can definitely be improved */
    float x = n;
    float y = 1;
    constexpr float e = 0.000001; /* e decides the accuracy level*/
    while (x - y > e) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}
