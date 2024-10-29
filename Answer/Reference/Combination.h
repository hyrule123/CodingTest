using uint64 = std::uint64_t;
uint64 Factorial(uint64 _num, uint64 _range) {
    uint64 ret = 1;

    for (uint64 i = 0; i < _range; ++i) {
        ret *= _num;
        --_num;
    }

    return ret;
}

uint64 Combination(uint64 _items, uint64 _selections) {
    uint64 range = std::min(_selections, _items - _selections);
    return Factorial(_items, range) / Factorial(range, range);
}