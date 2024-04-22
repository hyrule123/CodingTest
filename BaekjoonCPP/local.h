#pragma once
#define LOCAL

#ifdef LOCAL
#pragma warning(disable : 4996)

#include <iostream>
#define PAUSE printf("\n"); system("pause")

#define READ_INPUT (void)freopen("input.txt", "r", stdin)
#define WRITE_OUTPUT (void)freopen("output.txt", "w", stdout)

#endif //LOCAL