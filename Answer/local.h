#pragma once
#define LOCAL

#ifdef LOCAL
#define _CRT_SECURE_NO_WARNINGS

#define USING_IOSTREAM \
std::ios_base::sync_with_stdio(false);\
std::cin.tie(nullptr)

#define READ_INPUT (void)freopen("input.txt", "r", stdin)
#define WRITE_OUTPUT (void)freopen("output.txt", "w", stdout)

#endif //LOCAL