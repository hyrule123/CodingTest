#pragma once
#define LOCAL

#ifdef LOCAL
#define _CRT_SECURE_NO_WARNINGS

#define READ_INPUT (void)freopen("input.txt", "rt", stdin)
#define WRITE_OUTPUT (void)freopen("output.txt", "wt", stdout)

#endif //LOCAL

//std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);