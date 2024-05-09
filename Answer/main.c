#ifndef LOCAL
#define READ_INPUT (void)0
#define WRITE_OUTPUT (void)0
#endif //NDEF LOCAL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define maxLen 21

struct name {
    char s[maxLen];
    int len;

    struct name* pNext;
} typedef name;

static inline int IsPrime(const int _num) {
    if (_num <= 1) { return 0; }

    for (int i = 2; i <= _num / 2; ++i) {
        if (_num % i == 0) {
            return 0;
        }
    }

    return 1;
}

static inline int StringSame(const name* _name1, const name* _name2) {
    if (_name1->len != _name2->len) {
        return 0;
    }

    for (int i = 0; i < _name1->len; ++i) {
        if (_name1->s[i] != _name2->s[i]) {
            return 0;
        }
    }

    return 1;
}

static inline int StringLexicalAscend(const name* _name1, const name* _name2) {
    int l = _name1->len < _name2->len ? _name1->len : _name2->len;

    for (int i = 0; i < l; ++i) {
        if (_name1->s[i] == _name2->s[i]) { continue; }

        return _name1->s[i] < _name2->s[i];
    }

    return _name1->len < _name2->len;
}

static const unsigned int prime = 31;
static const unsigned int mod = 100000007;
static inline unsigned int Hash(const struct name* _name) {

    unsigned int ret = _name->s[0];

    if (0 < _name->len) {
        for (int i = 1; i < _name->len; ++i) {
            ret = (prime * ret + (unsigned int)_name->s[i]) % mod;
        }
    }

    return ret;
}

static void DeleteRecursive(struct name* _pName) {
    if (NULL == _pName) {
        return;
    }

    if (_pName->pNext) {
        DeleteRecursive(_pName->pNext);
        free(_pName->pNext);
    }
}

static void MergeSort(struct name** _arrName, struct name** _temp, const int _start, const int _end) {
    if (_start >= _end) {
        return;
    }

    const int mid = _start + (_end - _start) / 2;
    MergeSort(_arrName, _temp, _start, mid);
    MergeSort(_arrName, _temp, mid + 1, _end);

    int i = _start;
    int j = mid + 1;
    int cursor = _start;
    while (i <= mid && j <= _end) {
        if (StringLexicalAscend(_arrName[i], _arrName[j])) {
            _temp[cursor] = _arrName[i];
            ++cursor;
            ++i;
        }
        else {
            _temp[cursor] = _arrName[j];
            ++cursor;
            ++j;
        }
    }

    if (i <= mid) {
        for (; i <= mid; ++i, ++cursor) {
            _temp[cursor] = _arrName[i];
        }
    }
    else {
        for (; j <= _end; ++j, ++cursor) {
            _temp[cursor] = _arrName[j];
        }
    }

    memcpy(&(_arrName[_start]), &(_temp[_start]), sizeof(name*) * (_end - _start + 1));
}

//처음에는 이진탐색트리에 전부 삽입해서 정렬된 상태를 만들고, 한번에 출력하는 건줄 알았는데, 그게 아닌듯...
//문제는 듣보의 '보'(M으로 들어오는 애들)이 정렬되어 있는지 모르고
//출력의 첫번째줄에 몇개인지까지 적어놔야 한다는거임...
//결국 전부 받아서 검사해 본 뒤에야 순서를 결정할 수 있기 때문에 '듣'을 unordered_map에 넣고, '보'와 공통된 친구들을 따로 빼놓은 뒤, 정렬을 돌려야 함...
int main() {
    READ_INPUT;
    WRITE_OUTPUT;

    int N = 0, M = 0;
    (void)scanf("%d %d", &N, &M);

    int bucketSize = (int)((float)N * 1.2f);
    while (0 == IsPrime(bucketSize)) {
        ++bucketSize;
    }
    name** nameHashTable = (name**)malloc(sizeof(name*) * bucketSize);
    memset(nameHashTable, 0, sizeof(name*) * bucketSize);

    name input;
    memset(&input, 0, sizeof(name));

    //N Input
    for (int i = 0; i < N; ++i) {
        input.s[0] = '\0';
        input.len = 0;

        (void)scanf("%s", input.s);
        input.len = (int)strlen(input.s);

        int hash = Hash(&input) % bucketSize;

        name* dest = NULL;
        if (NULL == nameHashTable[hash]) {
            nameHashTable[hash] = (name*)malloc(sizeof(name));
            memset(nameHashTable[hash], 0, sizeof(name));
            dest = nameHashTable[hash];
        }
        else {
            name* iter = nameHashTable[hash];
            while (NULL != iter->pNext) {
                iter = iter->pNext;
            }
            iter->pNext = (name*)malloc(sizeof(name));
            dest = iter->pNext;
        }

        memcpy(dest, &input, sizeof(name));
    }


    name** DBJ = (name**)malloc(sizeof(name*) * N); //reserve
    memset(DBJ, 0, sizeof(name*) * N);
    int cursor = 0; //size

    //M Input
    for (int i = 0; i < M; ++i) {
        input.s[0] = '\0';
        input.len = 0;

        (void)scanf("%s", input.s);
        input.len = (int)strlen(input.s);

        int hash = Hash(&input) % bucketSize;

        if (NULL == nameHashTable[hash]) {
            continue;
        }
        else {
            name* iter = nameHashTable[hash];
            while (iter) {
                if (StringSame(&input, iter)) {
                    DBJ[cursor] = iter;
                    ++cursor;
                    break;
                }

                iter = iter->pNext;
            }
        }
    }

    {
        name** temp = malloc(sizeof(name*) * N);
        memset(temp, 0, sizeof(name*) * N);
        MergeSort(DBJ, temp, 0, cursor - 1);
        free(temp);
    }

    printf("%d\n", cursor);
    for (int i = 0; i < cursor; ++i) {
        printf("%s\n", DBJ[i]->s);
    }

    for (int i = 0; i < bucketSize; ++i) {
        if (NULL != nameHashTable[i]) {
            DeleteRecursive(nameHashTable[i]);
        }
    }
    free(nameHashTable);
    free(DBJ);
    return 0;
}
