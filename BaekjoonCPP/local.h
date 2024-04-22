#pragma once
#define LOCAL

#ifdef LOCAL
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#define PAUSE printf("\n"); system("pause")

#define READ_INPUT (void)freopen("input.txt", "r", stdin)
#define WRITE_OUTPUT (void)freopen("output.txt", "w", stdout)

#endif //LOCAL