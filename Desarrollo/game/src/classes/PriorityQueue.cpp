#ifndef PRIORITYQUEUE_C
#define PRIORITYQUEUE_C

#include "PriorityQueue.h"

template<class KeyType>
IndexedPriorityQLow<KeyType>::IndexedPriorityQLow(std::vector<KeyType>& keys,
int              MaxSize):m_vecKeys(keys),
                        m_iMaxSize(MaxSize),
                        m_iSize(0)
{
    m_Heap.assign(MaxSize+1, 0);
    m_invHeap.assign(MaxSize+1, 0);
}

template<class KeyType>
void IndexedPriorityQLow<KeyType>::Swap(int a, int b)
{
    int temp = m_Heap[a]; m_Heap[a] = m_Heap[b]; m_Heap[b] = temp;
    m_invHeap[m_Heap[a]] = a; m_invHeap[m_Heap[b]] = b;
}

template<class KeyType>
void IndexedPriorityQLow<KeyType>::ReorderUpwards(int nd)
{
    while ( (nd>1) && (m_vecKeys[m_Heap[nd/2]] > m_vecKeys[m_Heap[nd]]) )
    {
        Swap(nd/2, nd);

        nd /= 2;
    }
}

template<class KeyType>
void IndexedPriorityQLow<KeyType>::ReorderDownwards(int nd, int HeapSize)
{
    while (2*nd <= HeapSize)
    {
        int child = 2 * nd;

        if ((child < HeapSize) && (m_vecKeys[m_Heap[child]] > m_vecKeys[m_Heap[child+1]]))
        {
            ++child;
        }

        if (m_vecKeys[m_Heap[nd]] > m_vecKeys[m_Heap[child]])
        {
            Swap(child, nd);
            nd = child;
        }
        else
        {
            break;
        }
    }
}

template<class KeyType>
bool IndexedPriorityQLow<KeyType>::empty()const
{
    return (m_iSize==0);
}

template<class KeyType>
void IndexedPriorityQLow<KeyType>::insert(const int idx)
{
    if(m_iSize+1 <= m_iMaxSize)
    {
        ++m_iSize;
        m_Heap[m_iSize] = idx;
        m_invHeap[idx] = m_iSize;
        ReorderUpwards(m_iSize);
    }
}

template<class KeyType>
int IndexedPriorityQLow<KeyType>::Pop()
{
    Swap(1, m_iSize);
    ReorderDownwards(1, m_iSize-1);
    return m_Heap[m_iSize--];
}

template<class KeyType>
void IndexedPriorityQLow<KeyType>::ChangePriority(const int idx)
{
    ReorderUpwards(m_invHeap[idx]);
}

#endif // PRIORITYQUEUE_C
