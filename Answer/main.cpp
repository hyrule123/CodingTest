#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#define USING_IOSTREAM \
std::cin.tie(nullptr);\
std::ios_base::sync_with_stdio(false)

#include <stdio.h>
#include <iostream>
#include <cstring>  //memset
#include <limits>


#include <string>
#include <vector>
#include <list>
inline bool IsPrime(size_t _num) {
	if (_num <= 1) { return false; }
	if (_num <= 3) { return true; }
	if (_num % 2 == 0 || _num % 3 == 0) { return false; }

	for (size_t i = 5; i * i <= _num; i += 6) {
		if (_num % i == 0 || _num % (i + 2) == 0) return false;
	}

	return true;
}

template <typename K, typename Hasher>
concept is_hasher_valid = requires (K _key) {
	{ Hasher::Hash(_key) } -> std::same_as<size_t>;
};

template <typename K, typename V, typename Hasher> requires is_hasher_valid<K, Hasher>
class HashTable
{
public:
	struct Pair {
		K Key;
		V Value;
	};

	HashTable(size_t _bucketCapacity = 20011) : m_container{} {
		while (false == IsPrime(_bucketCapacity)) {
			++_bucketCapacity;
		}
		m_container.resize(_bucketCapacity);
	}
	~HashTable() {}

	const V* Insert(Pair&& _pair) {
		size_t hash = Hasher::Hash(_pair.Key) % m_container.size();

		std::list<Pair>& bucket = m_container[hash];

		//중복 검사 및 chaining
		auto iterEnd = bucket.end();
		for (auto iter = bucket.begin(); iter != iterEnd; ++iter) {
			if (iter->Key == _pair.Key) {
				return nullptr;
			}
		}

		bucket.push_back(std::forward<Pair>(_pair));

		return &(bucket.back().Value);
	}

	const V* Find(const K& _key) const {
		size_t hash = Hasher::Hash(_key) % m_container.size();

		const std::list<Pair>& bucket = m_container[hash];

		auto iterEnd = bucket.cend();
		for (auto iter = bucket.cbegin(); iter != iterEnd; ++iter) {
			if (_key == iter->Key) {
				return &(iter->Value);
			}
		}

		return nullptr;
	}

	V& operator[](const K& _key) {
		size_t hash = Hasher::Hash(_key) % m_container.size();

		std::list<Pair>& bucket = m_container[hash];

		//순회돌면서 검색
		auto iterEnd = bucket.end();
		for (auto iter = bucket.begin(); iter != iterEnd; ++iter) {
			if (_key == iter->Key) {
				return iter->Value;
			}
		}

		//못찾았다면 새로 하나 만들어서 반환
		bucket.push_back(Pair{ _key, {} });
		return bucket.back().Value;
	}

	const std::vector<std::list<Pair>>& GetContainer() const {
		return m_container;
	}

private:
	std::vector<std::list<Pair>> m_container;
};



struct StringHasher {
    inline static size_t Hash(const std::string_view _str)
    {
        constexpr const size_t p = 53;//31;
        constexpr const size_t mod = 1'000'000'007;
        size_t result = 0;

        if (_str.empty()) { return result; }

        //라빈-카프 문자열 해싱, 호너의 법칙
        size_t i = _str.size() - 1;
        result = static_cast<size_t>(_str[i]);
        for (; i > 0; --i) {
            result = (result * p + _str[i]) % mod;
        }
        result = (result + _str[0]) % mod;

        return result;
    }
};

int main() {
    USING_IOSTREAM;

    READ_INPUT;
    WRITE_OUTPUT;

    size_t N{}, M{};
    std::cin >> N >> M;

    //버킷사이즈 1.2배로 잡아준다
    HashTable<std::string, bool, StringHasher> 
        stringSet((size_t)((float)N * 1.2));

    using myPair = HashTable<std::string, bool, StringHasher>::Pair;

    std::string input{};
    input.reserve(500);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> input;
        stringSet[input];
    }

    size_t foundCount{};
    for (size_t i = 0; i < M; ++i) {
        std::cin >> input;

        auto* found = stringSet.Find(input);
        if (found) {
            ++foundCount;
        }
    }
    
    std::cout << foundCount;

    return 0;
}
