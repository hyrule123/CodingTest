#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

struct matrix {
	matrix(int _r, int _c) { 
		r = _r; 
		c = _c; 
		size = r * c;
		elem = new int[size];
		memset(elem, 0, size * sizeof(int));
	}
	matrix(std::istream& _in) {
		std::cin >> r >> c;
		size = r * c;
		elem = new int[size];
		for (int i = 0; i < size; ++i) {
			_in >> elem[i];
		}
	}
	~matrix() { delete[] elem; }

	int r, c, size;
	int* elem;
	int* operator[] (int _row) { return &(elem[_row * c]); }

	matrix operator * (matrix& _other) {
		matrix ret(r, _other.c);

		for (int _r = 0; _r < ret.r; ++_r) {
			int rIdx = _r * ret.c;
			for (int _c = 0; _c < ret.c; ++_c) {
				
				for (int _e = 0; _e < c; ++_e) {
					ret.elem[rIdx + _c] += (*this)[_r][_e] * _other[_e][_c];
				}
			}
		}

		return ret;
	}
};


int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	matrix A(std::cin), B(std::cin);
	matrix result = A * B;
	for (int _r = 0; _r < result.r; ++_r) {
		for (int _c = 0; _c < result.c; ++_c) {
			std::cout << result[_r][_c] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}
