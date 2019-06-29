//
// Created by User on 6/29/2019.
//

#ifndef EXERCIS_SIMPLEQUEUE_H
#define EXERCIS_SIMPLEQUEUE_H

#include <vector>
#include <array>
#include <algorithm> //std::swap
#include <initializer_list>
#include <ostream>
#include <stdexcept> //out_of_range exception

namespace simple
{


template<typename T, size_t SIZE=128>
class SimpleQueue
{
public:
    SimpleQueue()
        : mQueue(), mHead(), mTail(), mSize()
    {

    }
    SimpleQueue(const std::initializer_list<T>& il)
        :SimpleQueue()
    {
        //copy max SIZE elements
        auto end = il.size() >= SIZE ? il.begin() + SIZE : il.end();
        std::copy(il.begin(), end, mQueue.begin());
        mSize = std::distance(il.begin(), end);
        mHead = mSize -1;
        //mHead = (mSize == SIZE ? 0 : mSize);
    }

    SimpleQueue(const SimpleQueue& rhs) = default;
    SimpleQueue& operator=(const SimpleQueue& rhs) = default;

    SimpleQueue(SimpleQueue&& rhs) noexcept  =default;
    SimpleQueue& operator=(SimpleQueue&& rhs) noexcept  =default;

    ~SimpleQueue() = default;

    template<typename U>
    void push(U&& val)
    {
        static_assert(std::is_same<U, T>::value || std::is_convertible<U, T>::value, "U must be the same as T!");
        if(size() < SIZE)
        {
            mQueue[mHead] = std::forward<U>(val);
            if(++mHead == SIZE)
            {
                mHead = 0;
            }
            ++mSize;
        }
    }

    T pop()
    {
        if(empty())
        {
            throw std::out_of_range("can't pop an empty queue!");
        }
        auto& ret = mQueue[mTail];
        ++mTail;
        if(mTail == SIZE)
        {
            mTail = 0;
        }
        --mSize;

        return ret;
    }

    const T& front() const
    {
        return mQueue[mTail];
    }
    T& front()
    {
        return const_cast<T&>(static_cast<const SimpleQueue*>(this)->front());
    }

    const T& back() const
    {
        return mQueue[mHead];
    }
    T& back()
    {
        return const_cast<T&>(static_cast<const SimpleQueue*>(this)->back());
    }


    bool operator==(const SimpleQueue& rhs) const
    {
        if(mSize != rhs.mSize || mHead != rhs.mHead){
            return false;
        }
        for (size_t it = mTail; it != mHead; ++it)
        {
            if(it == SIZE){
                it = 0;
            }
            if(mQueue[it] != rhs.mQueue[it]){
                return false;
            }
        }

        return mQueue[mHead] == rhs.mQueue[mHead];
    }

    bool operator!=(const SimpleQueue& rhs) const
    {
        return !(*this == rhs);
    }
    friend void swap(SimpleQueue& lhs, SimpleQueue& rhs)
    {
        using std::swap;
        swap(lhs.mQueue, rhs.mQueue);
        swap(lhs.mHead, rhs.mHead);
        swap(lhs.mTail, rhs.mTail);
        swap(lhs.mSize, rhs.mSize);
    }


    size_t size() const { return mSize; }
    bool empty() const { return mSize == 0; }
    friend std::ostream& operator<<(std::ostream& os, const SimpleQueue& queue)
    {
        os<<"Queue size of "<<queue.size()<<":\n";
//        if(queue.size() == SIZE)
//        {
//            for(auto& it : queue.mQueue)
//            {
//                os<<it<<" ";
//            }
//        }
        auto elements = queue.size();
        for (size_t it = queue.mTail; elements; ++it, --elements) {
            if(it == SIZE){
                it = 0;
            }
            os<<queue.mQueue[it]<<" ";
        }

        os<<"\n";
        //os<<queue.mQueue[queue.mHead]<<"\n";
        return os;
    }
private:
    std::array<T, SIZE> mQueue;
    size_t mHead;
    size_t mTail;
    size_t mSize;
};

}//namespace simple
#endif //EXERCIS_SIMPLEQUEUE_H
