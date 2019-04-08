#ifndef CODINGPRACTICE_SIMPLEBINARYTREE_H
#define CODINGPRACTICE_SIMPLEBINARYTREE_H

#include <initializer_list>
#include <memory> //std::shared_ptr
#include <algorithm> //std::swap
#include <iostream>
#include <list>
#include <sstream>

namespace exercise
{
template<typename T>
class SimpleBinaryTree;

//TODO: create iterator for this
template<typename T>
bool operator==(const SimpleBinaryTree<T>& lhs, const SimpleBinaryTree<T>& rhs);

template<typename T>
bool operator!=(const SimpleBinaryTree<T>& lhs, const SimpleBinaryTree<T>& rhs);



template<typename T>
class SimpleBinaryTree
{
public:
    explicit SimpleBinaryTree(std::initializer_list<T>& list);
    SimpleBinaryTree();

    SimpleBinaryTree(const SimpleBinaryTree& rhs);
    SimpleBinaryTree& operator= (const SimpleBinaryTree& rhs);

    SimpleBinaryTree(SimpleBinaryTree&& rhs);
    SimpleBinaryTree& operator= (SimpleBinaryTree&& rhs);

    friend void swap(SimpleBinaryTree& lhs, SimpleBinaryTree& rhs){
        using std::swap;

        swap(lhs.mRoot, rhs.mRoot);
        swap(lhs.mSize, rhs.mSize);
    }

    auto size() const -> size_t;
    auto empty() const -> bool;

    auto find(const T& val) const -> const T&;
    auto insert(const T& val) -> bool;
    auto remove(const T& val) -> bool;

    auto height() const -> size_t;

    friend std::ostream& operator<<(std::ostream& os, const SimpleBinaryTree& tree)
    {
        std::list<std::pair<T, size_t>>& node_list= SortNodesByHeightImpl(tree.mRoot, 0);
        node_list.sort([](const std::pair<T, size_t>& a,const std::pair<T, size_t>& b){
            return a.second < b.second;
        });
        //size_t height = tree.height();
        for(auto element: node_list){
            std::cout<<"val:level = ("<<element.first<<", "<<element.second<<") "<<std::endl;
        }

        node_list.clear();
        return os;
    }
public:
    class iterator;

    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using size_type         = size_t;
    using difference_type   = std::ptrdiff_t;

    auto begin() -> iterator;
    auto end() -> iterator ;

    //https://stackoverflow.com/questions/7758580/writing-your-own-stl-container/7759622#7759622
    class iterator
    {
    public:
        using value_type        = SimpleBinaryTree::value_type;
        using pointer           = SimpleBinaryTree::pointer;
        using reference         = SimpleBinaryTree::reference;
        using size_type         = SimpleBinaryTree::size_type;
        using difference_type   = SimpleBinaryTree::difference_type;

        using iterator_tag = std::forward_iterator_tag;

        struct TreeNode;
    public:
        iterator(std::shared_ptr<TreeNode> root);

        auto operator==(const iterator&) const -> bool;
        auto operator!=(const iterator&) const -> bool;

        auto operator++() -> iterator& ;
        auto operator++(int) -> iterator ;

        auto operator*() const -> reference;
        auto operator->() const -> pointer;
    private:
        static auto FindParentImpl(std::shared_ptr<TreeNode> root, const T& val) -> std::shared_ptr<TreeNode>;
    private:
        std::shared_ptr<TreeNode> mRoot;
        const T& mCurrVal;
    };

    void InsertNode(T val){
        mRoot = InsertNodeImpl(mRoot, val);
    }
    void PrintTree()
    {
        std::list<std::pair<T, size_t>>& tmp_node_list= SortNodesByHeightImpl(mRoot, 0);
        for(auto element: tmp_node_list){
            std::cout<<"val:level = ("<<element.first<<", "<<element.second<<") "<<std::endl;
        }

        tmp_node_list.clear();
    }

private:

    struct TreeNode
    {
        T val;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        //std::shared_ptr<TreeNode> parent

        explicit TreeNode(T value): val(value), left{nullptr}, right{nullptr} {}
    };

private:
    std::shared_ptr<TreeNode> InsertNodeImpl(std::shared_ptr<TreeNode>& node, const T& val)
    {
        if(!node){
            ++mSize;
            return std::make_shared<TreeNode>(val);
        }

        if(val < node->val){
            node->left = InsertNodeImpl(node->left, val);
        }
        else if(val > node->val){
            node->right = InsertNodeImpl(node->right, val);
        }

        return node;
    }

    static std::list<std::pair<T, size_t>>& SortNodesByHeightImpl(std::shared_ptr<TreeNode> node, size_t level)
    {
        static std::list<std::pair<T, size_t>> node_list;
        if(!node){
            return node_list;
        }
        node_list = SortNodesByHeightImpl(node->left, level + 1);
        node_list = SortNodesByHeightImpl(node->right, level + 1);
        node_list.push_back(std::make_pair(node->val, level));

        return node_list;
    }

private:
    std::shared_ptr<TreeNode> mRoot;
    std::size_t mSize;
};


template<typename T>
SimpleBinaryTree<T>::SimpleBinaryTree(std::initializer_list<T>& list)
{

}

template<typename T>
SimpleBinaryTree<T>::SimpleBinaryTree(): mRoot{nullptr}, mSize(0)
{

}

template<typename T>
SimpleBinaryTree<T>::SimpleBinaryTree(const SimpleBinaryTree& rhs)
{

}

template<typename T>
SimpleBinaryTree<T>& SimpleBinaryTree<T>::operator= (const SimpleBinaryTree& rhs)
{

}

template<typename T>
SimpleBinaryTree<T>::SimpleBinaryTree(SimpleBinaryTree&& rhs)
{

}

template<typename T>
SimpleBinaryTree<T>& SimpleBinaryTree<T>::operator= (SimpleBinaryTree&& rhs)
{

}

template<typename T>
auto SimpleBinaryTree<T>::size() const -> size_t
{
    return mSize;
}

template<typename T>
auto SimpleBinaryTree<T>::empty() const -> bool
{
    return size() == 0;
}

template<typename T>
auto SimpleBinaryTree<T>::find(const T& val) const -> const T&
{

}

template<typename T>
auto SimpleBinaryTree<T>::insert(const T& val) -> bool
{
    mRoot = InsertNodeImpl(mRoot, val);
}

template<typename T>
auto SimpleBinaryTree<T>::remove(const T& val) -> bool
{

}

template<typename T>
auto SimpleBinaryTree<T>::height() const -> size_t
{
    auto node = mRoot;
    size_t height = 0;
    while(node){
        node = node->left;
        ++height;
    }
    return height;
}

template<typename T>
auto SimpleBinaryTree<T>::begin() -> iterator
{
    return iterator{mRoot};
}

template<typename T>
auto SimpleBinaryTree<T>::end() -> iterator
{
    return iterator{nullptr};
}



template<typename T>
SimpleBinaryTree<T>::iterator::iterator(std::shared_ptr<TreeNode> root): mRoot(root), mCurrVal()
{
    if(mRoot){
        auto prev{mRoot};
        auto node{mRoot->left};
        while(node){
            prev = node;
            node = node->left;
        }
        mCurrVal = prev->val;
    }
}

template<typename T>
auto SimpleBinaryTree<T>::iterator::operator==(const iterator& rhs) const -> bool
{
    return mRoot && rhs.mRoot && mCurrVal == mCurrVal;
}

template<typename T>
auto SimpleBinaryTree<T>::iterator::operator!=(const iterator& rhs) const -> bool
{
    return !(*this == rhs);
}

template<typename T>
auto SimpleBinaryTree<T>::iterator::operator++() -> iterator&
{

}

template<typename T>
auto SimpleBinaryTree<T>::iterator::operator++(int) -> iterator
{

}

template<typename T>
auto SimpleBinaryTree<T>::iterator::operator*() const -> reference
{

}

template<typename T>
auto SimpleBinaryTree<T>::iterator::operator->() const -> pointer
{

}

//static
template<typename T>
auto SimpleBinaryTree<T>::iterator::FindParentImpl(std::shared_ptr<TreeNode> root, const T& val) -> std::shared_ptr<TreeNode>
{

}



}//namespace exercise

#endif //CODINGPRACTICE_SIMPLEBINARYTREE_H
