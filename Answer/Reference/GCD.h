
//Euclidian algorithm
inline int GCD(int _a, int _b) {
    int r{};
    //요약: (b가 0이 될 때까지) b로 나눈 나머지를 구하고 -> b를 그 나머지로 나누기를 반복한다.
    while (_b != 0) {
        r = _a % _b;
        _a = _b;
        _b = r;
    }
    return _a;
}