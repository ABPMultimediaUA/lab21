#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>

template<class KeyType>
class IndexedPriorityQLow
{
    private:

        std::vector<KeyType>&  m_vecKeys;
        std::vector<int> m_Heap;
        std::vector<int> m_invHeap;
        int m_iMaxSize;
        int m_iSize;

        void Swap(int a, int b);
        void ReorderUpwards(int nd);
        void ReorderDownwards(int nd, int HeapSize);

    public:

        IndexedPriorityQLow(std::vector<KeyType>& keys, int MaxSize);
        bool empty()const;
        void insert(const int idx);
        int Pop();
        void ChangePriority(const int idx);
};

#include "PriorityQueue.cpp"

#endif // PRIORITYQUEUE_H
