
//Euclidian algorithm
inline int GCD(int _a, int _b) {
    int r{};
    //���: (b�� 0�� �� ������) b�� ���� �������� ���ϰ� -> b�� �� �������� �����⸦ �ݺ��Ѵ�.
    while (_b != 0) {
        r = _a % _b;
        _a = _b;
        _b = r;
    }
    return _a;
}