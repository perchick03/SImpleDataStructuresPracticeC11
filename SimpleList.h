//
// Created by User on 6/27/2019.
//

#ifndef EXERCIS_SIMPLELIST_H
#define EXERCIS_SIMPLELIST_H

#include <algorithm> //std::swap
#include <ostream>
#include <initializer_list>

namespace simple
{

//emplace
//insert
//remove


template<typename T>
class SimpleList
{
public:
    struct Node
    {
        T m_data;
        Node* p_next = nullptr;
    };

public:

    SimpleList() = default;

    explicit SimpleList(const std::initializer_list<T>& il)
        : SimpleList()
    {
        auto iter = il.begin();
        pHead = new Node{*iter};
        ++iter;
        auto node = pHead;
        for (; iter < il.end(); ++iter) {
            node->p_next = new Node{*iter};
            node = node->p_next;
        }

        mSize = il.size();
    }

    ~SimpleList()
    {
        clear();
    }

    SimpleList(const SimpleList& rhs)
        : SimpleList()
    {
        pHead = new Node{rhs.pHead->m_data};
        auto node = pHead;
        auto rhs_node = rhs.pHead;
        while(rhs_node = rhs_node->p_next){
            node->p_next = new Node{rhs_node->m_data};
            node = node->p_next;
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


    void clear()
    {
        if(!pHead){
            return;
        }
        auto node = pHead;
        while(node = node->p_next)
        {
            delete pHead;
            pHead = node;
        }
        mSize = 0;
        pHead = nullptr;
    }

    auto empty() const  { return mSize == 0; }
    auto size() const   { return mSize; }

    //TODO: is this Kosher?
    //https://stackoverflow.com/questions/8193102/initializer-list-and-move-semantics
    //SimpleList(std::initializer_list<T>&& il) noexcept;


    //T should support op==, op!=
    bool operator== (const SimpleList& rhs) const
    {
        if(!pHead || !rhs.pHead || mSize != rhs.mSize){
            return false;
        }
        auto this_node = pHead;
        auto rhs_node = rhs.pHead;

        while(this_node && rhs_node){
            if(this_node->m_data != rhs_node->m_data){
                return false;
            }
            this_node = this_node->p_next;
            rhs_node = rhs_node->p_next;
        }

        return true;
    }
    bool operator!= (const SimpleList& rhs) const {
        return !(*this == rhs);
    }
    friend void swap(SimpleList& rhs, SimpleList& lhs) noexcept
    {
        using std::swap;
        swap(rhs.pHead, lhs.pHead);
        swap(rhs.mSize, lhs.mSize);
    }

    //T should support operator<<
    friend std::ostream& operator<<(std::ostream& os, const SimpleList& sl)
    {
        os<<"list "<<sl.mSize<<": {";
        auto node = sl.pHead;
        while(node)
        {
            os<<node->m_data<<(node->p_next ? ", " : "");
            node = node->p_next;
        }
        os<<"}\n";
        return os;
    }
private:
    Node* pHead = nullptr;
    std::size_t mSize = 0;
};

}//namespace simple
#endif //EXERCIS_SIMPLELIST_H
