#ifndef EXERCIS_SIMPLELIST_H
#define EXERCIS_SIMPLELIST_H

#include <algorithm> //std::swap
#include <ostream>
#include <initializer_list>

namespace simple
{


template<typename T>
class SimpleList
{
private:
    struct Node
    {
        T mData;
        Node* pNext = nullptr;
    };

public:

    SimpleList() = default;

    SimpleList(const std::initializer_list<T>& il)
        : SimpleList()
    {
        auto iter = il.begin();
        mHead = new Node{*iter};
        ++iter;
        auto node = mHead;
        for (; iter < il.end(); ++iter) {
            node->pNext = new Node{*iter};
            node = node->pNext;
        }

        mSize = il.size();
    }


    SimpleList(const SimpleList& rhs)
        : SimpleList()
    {
        mHead = new Node{rhs.mHead->mData};
        auto node = mHead;
        auto rhs_node = rhs.mHead;
        while(rhs_node = rhs_node->pNext){
            node->pNext = new Node{rhs_node->mData};
            node = node->pNext;
        }
        mSize = rhs.mSize;
    }
    SimpleList& operator=(const SimpleList& rhs) noexcept
    {
        auto tmp{rhs};
        swap(*this, tmp);

        return *this;
    }

    SimpleList(SimpleList&& rhs) noexcept
        :SimpleList()
    {
        swap(*this, rhs);
    }

    SimpleList& operator=(SimpleList&& rhs) noexcept
    {
        swap(*this, rhs);

        return *this;
    }

    ~SimpleList()
    {
        clear();
    }

    void clear() noexcept
    {
        auto p = std::exchange(mHead, nullptr);
        while(p)
        {
            delete std::exchange(p, p->pNext);
        }
    }

    bool empty() const  { return mSize == 0; }
    size_t size() const   { return mSize; }


    //T should support op==, op!=
    bool operator== (const SimpleList& rhs) const
    {
        if(!mHead || !rhs.mHead)
        {
            if(!mHead && !rhs.mHead){
                return true;
            }
            return false;
        }
        if(mSize != rhs.mSize){
            return false;
        }
        auto this_node = mHead;
        auto rhs_node = rhs.mHead;

        while(this_node && rhs_node){
            if(this_node->mData != rhs_node->mData){
                return false;
            }
            this_node = this_node->pNext;
            rhs_node = rhs_node->pNext;
        }

        return true;
    }
    bool operator!= (const SimpleList& rhs) const {
        return !(*this == rhs);
    }
    friend void swap(SimpleList& rhs, SimpleList& lhs) noexcept
    {
        using std::swap;
        swap(rhs.mHead, lhs.mHead);
        swap(rhs.mSize, lhs.mSize);
    }

    //T should support operator<<
    friend std::ostream& operator<<(std::ostream& os, const SimpleList& sl)
    {
        os<<"list "<<sl.mSize<<": {";
        auto node = sl.mHead;
        while(node)
        {
            os<<node->mData<<(node->pNext ? ", " : "");
            node = node->pNext;
        }
        os<<"}\n";
        return os;
    }
private:
    Node* mHead = nullptr;
    std::size_t mSize = 0;
};

}//namespace simple
#endif //EXERCIS_SIMPLELIST_H
