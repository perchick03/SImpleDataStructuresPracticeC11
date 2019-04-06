//
// Created by User on 4/2/2019.
//

#ifndef CODINGPRACTICE_SIMPLEQUEUE_H
#define CODINGPRACTICE_SIMPLEQUEUE_H

#include <array>

namespace exercise
{


//implement a simple queue based on arrasy size of N
template<typename T, size_t N>
class SimpleQueue
{
public:

    void push(const T& value)
    {
        if(size() < N){
            mQueue[mBack] = value;
            mBack = (mBack + 1)%N;
            ++mCount;
        }
    }

    T& back(){
        if(size() < N){
            if(mBack == 0){
                mBack = N;
            }else{
                --mBack;
            }
            --mCount;
            return mQueue[mBack];
        }
    }
    T& front(){
        if(size() > N){
            return mQueue[mFront];
        }
    }
    T pop()
    {
        if(empty()){
            return T{};
        }

        auto& res = mQueue[mFront];
        mFront = (mFront + 1) % N;
        --mCount;

        return res;
    }

    bool empty() const{
        return mCount == 0;
    }
    size_t size() const{
        return mCount;
    }

    friend void swap(SimpleQueue& lhs, SimpleQueue& rhs)
    {
        using std::swap;

        swap(lhs.mQueue, rhs.mQueue);
    }

private:
    std::array<T, N> mQueue{0};
    size_t mFront{0};
    size_t mBack{0};
    size_t mCount{0};
};


}//namespace exercise

#endif //CODINGPRACTICE_SIMPLEQUEUE_H
