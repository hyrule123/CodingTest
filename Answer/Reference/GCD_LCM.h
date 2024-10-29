using uint = std::uint32_t;
uint GCD(uint _a, uint _b) {

    while (_b != 0) {
        uint r = _a % _b;
        _a = _b;
        _b = r;
    }

    return _a;
}

uint LCM(uint _a, uint _b) {
    //a * b / GCD(a,b) -> overflow 방지를 위해 a / gcd(a, b) * b
    return (_a / GCD(_a, _b) * _b);
}