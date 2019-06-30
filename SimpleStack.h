//
// Created by User on 6/28/2019.
//

#ifndef EXERCIS_SIMPLESTACK_H
#define EXERCIS_SIMPLESTACK_H

#include <algorithm>  //std::swap
#include <initializer_list>
#include <ostream>
#include <memory>
#include <vector>


namespace simple
{


template<typename T>
class SimpleStack
{
public:
    friend void swap(SimpleStack& lhs, SimpleStack& rhs)
    {
        using std::swap;
        swap(lhs.mStack, rhs.mStack);
    }

    friend std::ostream& operator<<(std::ostream& os, const SimpleStack& stack)
    {
        os<<"Stack size "<<stack.size()<<"\n";
        for (auto it = stack.mStack.rbegin(); it != stack.mStack.rend(); ++it)
        {
            os<<*it<<"\n";
        }
        return os;
    }
public:

    SimpleStack() = default;

    SimpleStack(const std::initializer_list<T>& il)
        :mStack(il)
    {

    }

    SimpleStack(const SimpleStack& rhs)
        :mStack(rhs.mStack.begin(), rhs.mStack.end())
    {

    }

    SimpleStack(SimpleStack&& rhs) noexcept
        :mStack(std::move(rhs.mStack))
    {

    }

    SimpleStack& operator=(const SimpleStack& rhs)
    {
        auto tmp(rhs);
        swap(*this, tmp);

        return *this;
    }

    SimpleStack& operator=(SimpleStack&& rhs) noexcept
    {
        swap(*this, rhs);

        return *this;
    }

    const T& top()
    {
        return mStack.back();
    }


    template<typename U>
    void push(U&& val){
        static_assert(std::is_same<U, T>::value || std::is_convertible<U, T>::value, "U must be the same as T!");
        mStack.push_back(std::forward<U>(val));
    }

    void pop()
    {
        mStack.pop_back();
    }

    template<class... Args>
    void emplace(Args&&... args)
    {
        mStack.emplace(mStack.end(), std::forward<Args>(args)...);
    }

    bool empty() const{
        return mStack.empty();
    }
    size_t size() const{
        return mStack.size();
    }

    bool operator== (const SimpleStack& rhs) const
    {
        return mStack == rhs.mStack;
    }
    bool operator!= (const SimpleStack& rhs) const
    {
        return !(*this == rhs);
    }


private:
    std::vector<T> mStack;
};

}//namespace simple


#endif //EXERCIS_SIMPLESTACK_H
