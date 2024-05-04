//Templatized HeapSort
#include <vector>
#include <type_traits>
template <typename CompareStruct, typename T = CompareStruct::Type>
concept is_comparable = requires(T _a, T _b)
{
    { CompareStruct::Compare(_a, _b) } -> std::same_as<bool>;
};

//CompareStruct���� ���ǵ� �� �Լ��� ���� �ִ���/�ּ������� ����
template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void Heapify(std::vector<T>& _arr, const size_t _arrSize, const size_t _idx)
{
    //���� ũ�ų� ���� ���� ���� ������ �ִ� ����
    //�ʱⰪ = �θ� ���
    size_t extremeIdx = _idx;
    //����, ������ �ڽ� ���(* 2 + 1 or 2)
    size_t left = 2 * _idx + 1;
    size_t right = 2 * _idx + 2;

    //���� �ڽ� ���� �θ� ��带 ��, �ڽ� ��尡 �񱳿��� true�� ��ȯ�Ǹ� �ε����� ����
    if (left < _arrSize && CompareStruct::Compare(_arr[extremeIdx], _arr[left]))
    {
        extremeIdx = left;
    }

    //������ �ڽ� ���� �θ� ��带 ��, �θ� ���(Ȥ�� ���� ���� �� �� �� ũ�ٰ� ������ ��� �ε����� ����)
    if (right < _arrSize && CompareStruct::Compare(_arr[extremeIdx], _arr[right]))
    {
        extremeIdx = right;
    }

    if (extremeIdx != _idx)
    {
        //�شܰ��� ����Ʈ�� ��Ģ�� �´� �ڸ��� �Ű��ش�.
        std::swap(_arr[_idx], _arr[extremeIdx]);

        //���� ����� ��忡 ���� ����Ʈ�� ��Ģ �˻�(���)
        Heapify<CompareStruct, T>(_arr, _arrSize, extremeIdx);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void BuildHeap(std::vector<T>& _arr)
{
    //��ü �������� ������ ������ �θ� ����� ���ɼ��� �ִ� �ֵ鸸 ����.
    //�θ� ����� ���ɼ��� �ִ� ����� ���� �κк��� �ϳ��� �ö�´�.
    //��Ʈ���� ��� �ڽĳ���� ������ ����
    const size_t arrSize = _arr.size();
    for (size_t i = _arr.size() / 2; i != -1; --i)
    {
        Heapify<CompareStruct, T>(_arr, arrSize, i);
    }
}

template <typename CompareStruct, typename T = CompareStruct::Type> requires is_comparable<CompareStruct>
void HeapSort(std::vector<T>& _arr)
{
    //������ ��Ģ�� �°� ����
    BuildHeap<CompareStruct, T>(_arr);

    for (size_t i = _arr.size() - 1; i > 0; --i)
    {
        //������ ��Ģ�� �°� �ȴٸ�, ���� ū/���� ���� 0�� ��Ʈ��忡 ������ ���̴�.
        //�� ���� �迭�� ���κп� �ϳ��� ä���ش�.
        std::swap(_arr[0], _arr[i]);

        //��Ʈ ��忡 �� ���� ������ ��Ģ�� ���� �����Ƿ�, �ٽ� ��Ģ�� �°� Ʈ���� ��迭�Ѵ�.
        //��迭�ϸ� ��Ʈ ��忡�� �������� ū ���� ������ �ȴ�. 
        Heapify<CompareStruct, T>(_arr, i, 0);
    }
}