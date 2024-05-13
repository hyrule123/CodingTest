
//Euclidian algorithm
inline int GCD(int _a, int _b) {
    int r{};
    while (_b != 0) {
        r = _a % _b;
        _a = _b;
        _b = r;
    }
    return _a;
}