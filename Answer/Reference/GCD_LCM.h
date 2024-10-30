using ull = std::uint32_t;
ull GCD(ull _a, ull _b) {

    while (_b != 0) {
        ull r = _a % _b;
        _a = _b;
        _b = r;
    }

    return _a;
}

ull LCM(ull _a, ull _b) {
    //a * b / GCD(a,b) -> overflow 방지를 위해 a / gcd(a, b) * b
    return (_a / GCD(_a, _b) * _b);
}