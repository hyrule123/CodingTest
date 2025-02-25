//Euclidian algorithm
/*
* 두 양의 정수 a, b ( a > b )에 대하여 
a = bq + r ( 0 ≤ r < b ) 이라 하면, (* a ≡ r(mod b) )
a,b의 최대공약수는 
b,r의 최대공약수와 같다. 즉,
gcd(a, b) = gcd(b, r)
r = 0이라면, a, b의 최대공약수는 b가 된다.
*/
inline int GCD(int _a, int _b) {
    int r{};
    while (_b != 0) {
        r = _a % _b;
        _a = _b;
        _b = r;
    }
    return _a;
}