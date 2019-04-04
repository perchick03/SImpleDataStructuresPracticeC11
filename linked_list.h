//
// Created by User on 4/1/2019.
//
#include <memory>
#include <utility>
#include <algorithm>

#ifndef CODINGPRACTICE_LINKED_LIST_H
#define CODINGPRACTICE_LINKED_LIST_H

namespace exercise
{
template<typename T, class Allocator>
class list;

//TODO: need to create iterator for this
//https://github.com/AlexanderJDupree/LinkedListsCPP/blob/master/include/linear_linked_list.hpp here is an example
template<typename T, class Allocator>
bool operator==(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs);

template<typename T, class Allocator>
bool operator!=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs);

template<typename T, class Allocator = std::allocator<T>>
class list
{
public:
    list() = default;
    ~list();

    list(const list& rhs);
    list& operator= (list rhs);

    list(list&& rhs);
    list& operator=(list&& rhs);


    void push_back(const T& value);
    void push_front(const T& value);

    T& front();
    T& back();

    void pop_back();
    void pop_front();

    bool empty() const;
    size_t size() const;

    void sort();
    void flip();
    void remove_duplicates();



    friend void swap(list& lhs, list& rhs){
        using std::swap;

        lhs.pHead.swap(rhs.pHead);
        swap(lhs.mCount, rhs.mCount);
    }

    friend std::ostream& operator<<(std::ostream& os, const list& list){
        if(!list.pHead){
            return os;
        }
        auto pNode = list.pHead.get();
        while(pNode){
            os<<"("<<pNode->val<<")-->";
            pNode = pNode->next.get();
        }
        os<<"null\n";

        return os;
    }

    T& find_N_from_tail(size_t N);
private:
    struct Node
    {
        explicit Node(const T& value): next(nullptr), val(value) {}
        std::unique_ptr<Node> next;
        T val;
    };
    void ClearListImpl(){
        while(pHead){
            pHead = std::move(pHead->next);
        }
    }
    void PushToSortedImpl(std::unique_ptr<Node>& node);

    auto GetTailImpl();
private:
    std::unique_ptr<Node> pHead{nullptr};
    size_t mCount{0};

};


template<typename T, class Allocator>
list<T, Allocator>::~list() {
    ClearListImpl();
}


template<typename T, class Allocator>
list<T, Allocator>::list(const list& rhs)
{
    auto node{rhs.pHead.get()};
    while(node)
    {
        push_back(node->val);
        node = node->next.get();
    }
}

template<typename T, class Allocator>
list<T, Allocator>& list<T, Allocator>::operator= (list rhs)
{
    swap(*this, rhs);

    return *this;
}

template<typename T, class Allocator>
list<T, Allocator>::list(list&& rhs): pHead(std::move(rhs.pHead)), mCount(std::move(rhs.pHead))
{

}

template<typename T, class Allocator>
list<T, Allocator>& list<T, Allocator>::operator=(list&& rhs)
{
    pHead(std::move(rhs.pHead));
    mCount(std::move(rhs.pHead));
}

template<typename T, class Allocator>
void list<T, Allocator>::push_back(const T& value)
{
    auto new_node{std::make_unique<Node>(value)};
    ++mCount;
    if(!pHead){
        pHead = std::move(new_node);
        return;
    }
    auto node = pHead.get();
    while(node->next){
        node = node->next.get();
    }
    node->next = std::move(new_node);

}
template<typename T, class Allocator>
void list<T, Allocator>::push_front(const T& value)
{
    auto new_node{std::make_unique<Node>(value)};
    ++mCount;
    if(pHead){
        new_node->next = std::move(pHead);
    }
    pHead = std::move(new_node);
}
template<typename T, class Allocator>
T& list<T, Allocator>::front()
{
    return pHead->val;
}

template<typename T, class Allocator>
T& list<T, Allocator>::back()
{
    auto pNode = pHead.get();
    while(pNode->next){
        pNode = pNode->next.get();
    }
    return pNode->val;
}

template<typename T, class Allocator>
void list<T, Allocator>::pop_front()
{
    if(!pHead){
        return;
    }
    pHead = std::move(pHead->next);
    --mCount;
}

template<typename T, class Allocator>
void list<T, Allocator>::pop_back()
{
    if(!pHead){
        return;
    }
    if(!pHead->next){
        pHead.release();
        --mCount;
        return;
    }
    auto node = pHead.get();
    while(node->next->next.get())
    {
        node = node->next.get();
    }
    node->next.release();
    --mCount;
}


template<typename T, class Allocator>
bool list<T, Allocator>::empty() const { return mCount == 0;}

template<typename T, class Allocator>
size_t list<T, Allocator>::size() const { return mCount;}


template<typename T, class Allocator>
void list<T, Allocator>::sort()
{
    list<T, Allocator> tmp_list{};
    while(pHead){
        auto tmp_node {std::move(pHead)};
        pHead = std::move(tmp_node->next);
        tmp_list.PushToSortedImpl(tmp_node);
        ++tmp_list.mCount;
    }
    *this = tmp_list;
}

//TODO: change this to push_back/push_front instead of passing a node
template<typename T, class Allocator>
void list<T, Allocator>::PushToSortedImpl(std::unique_ptr<Node>& node)
{
    if(!pHead || node->val < pHead->val)
    {
        node->next = std::move(pHead);
        pHead = std::move(node);
        return;
    }

    auto prev{pHead.get()};
    auto curr{prev->next.get()};
    while(curr){
        if(node->val <= curr->val){
            node->next = std::move(prev->next);
            prev->next = std::move(node);
            return;
        }
        prev = curr;
        curr = curr->next.get();
    }
    prev->next = std::move(node);
}


template<typename T, class Allocator>
void list<T, Allocator>::remove_duplicates()
{
    if(mCount < 2){
        return;
    }
    auto iter{pHead.get()};

    while(iter){
        auto prev_runner {iter};
        auto runner {iter->next.get()};
        while(runner){
            if(runner->val == iter->val){
                prev_runner->next = std::move(runner->next);
                --mCount;
            }
            else{
                prev_runner = runner;
            }
            runner = prev_runner->next.get();
        }
        iter = iter->next.get();

    }
}

template<typename T, class Allocator>
void list<T, Allocator>::flip()
{
    if(mCount < 2){
        return;
    }

    decltype(pHead) prev {nullptr};
    auto curr{std::move(pHead)};
    while(curr){
        auto saved_next {std::move(curr->next)};
        curr->next = std::move(prev);
        prev = std::move(curr);
        curr = std::move(saved_next);
    }
    pHead = std::move(prev);
}

template<typename T, class Allocator>
T& list<T, Allocator>::find_N_from_tail(size_t N)
{
    if(mCount < N){
        auto tail = GetTailImpl();
        return tail ? tail->val : T{}; //TODO: how to implement undefined behavior here? throw exception?
    }
    auto iter {pHead.get()};
    size_t node_count = N;
    while(node_count)
    {
        iter = iter->next.get();
        --node_count;
    }
    auto Nth_node{pHead.get()};
    while(iter){
        iter = iter->next.get();
        Nth_node = Nth_node->next.get();
    }

    return Nth_node->val;
}


template<typename T, class Allocator>
auto list<T, Allocator>::GetTailImpl()
{
    if(!pHead){
        return nullptr;
    }
    auto iter{pHead.get()};
    while(iter->next){
        iter = iter->next.get();
    }
    return iter.get();
}

}//exercise
#endif //CODINGPRACTICE_LINKED_LIST_H
