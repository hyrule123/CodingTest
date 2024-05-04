//Templatized HeapSort
#include <vector>
#include <type_traits>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b)
{
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};

//CompareStruct에서 정의된 비교 함수에 따라 최대힙/최소힙으로 정렬
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void Heapify(std::vector<T>& _arr, const size_t _arrSize, const size_t _idx)
{
    //제일 크거나 제일 작은 값을 가지고 있는 변수
    //초기값 = 부모 노드
    size_t extremeIdx = _idx;
    //왼쪽, 오른쪽 자식 노드(* 2 + 1 or 2)
    size_t left = 2 * _idx + 1;
    size_t right = 2 * _idx + 2;

    //왼쪽 자식 노드와 부모 노드를 비교, 자식 노드가 비교에서 true가 반환되면 인덱스를 변경
    if (left < _arrSize && CompareStruct::Compare(_arr[extremeIdx], _arr[left]))
    {
        extremeIdx = left;
    }

    //오른쪽 자식 노드와 부모 노드를 비교, 부모 노드(혹은 왼쪽 노드와 비교 후 더 크다고 판정될 경우 인덱스를 변경)
    if (right < _arrSize && CompareStruct::Compare(_arr[extremeIdx], _arr[right]))
    {
        extremeIdx = right;
    }

    if (extremeIdx != _idx)
    {
        //극단값을 이진트리 규칙에 맞는 자리로 옮겨준다.
        std::swap(_arr[_idx], _arr[extremeIdx]);

        //값이 변경된 노드에 대해 이진트리 규칙 검사(재귀)
        Heapify<CompareStruct, T>(_arr, _arrSize, extremeIdx);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void BuildHeap(std::vector<T>& _arr)
{
    //전체 사이즈의 반으로 나누면 부모 노드일 가능성이 있는 애들만 남음.
    //부모 노드일 가능성이 있는 노드의 뒤쪽 부분부터 하나씩 올라온다.
    //루트노드는 모든 자식노드의 영향을 받음
    const size_t arrSize = _arr.size();
    for (size_t i = _arr.size() / 2; i != -1; --i)
    {
        Heapify<CompareStruct, T>(_arr, arrSize, i);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void HeapSort(std::vector<T>& _arr)
{
    //이진힙 규칙에 맞게 변경
    BuildHeap<CompareStruct, T>(_arr);

    for (size_t i = _arr.size() - 1; i > 0; --i)
    {
        //이진힙 규칙에 맞게 된다면, 가장 큰/작은 값이 0번 루트노드에 들어왔을 것이다.
        //이 값을 배열의 끝부분에 하나씩 채워준다.
        std::swap(_arr[0], _arr[i]);

        //루트 노드에 온 수는 이진힙 규칙에 맞지 않으므로, 다시 규칙에 맞게 트리를 재배열한다.
        //재배열하면 루트 노드에는 다음으로 큰 수가 들어오게 된다. 
        Heapify<CompareStruct, T>(_arr, i, 0);
    }
}