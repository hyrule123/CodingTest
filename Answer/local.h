#pragma once
#define LOCAL

#ifdef LOCAL
#define _CRT_SECURE_NO_WARNINGS
#define LOCAL_IO (void)freopen("input.txt", "rt", stdin); (void)freopen("output.txt", "wt", stdout)
#endif //LOCAL

//std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);