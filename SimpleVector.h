//
// Created by User on 6/26/2019.
//

#ifndef EXERCIS_SIMPLEVECTOR_H
#define EXERCIS_SIMPLEVECTOR_H


#include <algorithm> //std::swap
#include <ostream>
#include <initializer_list>

namespace simple
{



class SimpleVector
{
public:
    explicit SimpleVector(size_t size = 0);
    explicit SimpleVector(const std::initializer_list<int>& il);

    ~SimpleVector();

    SimpleVector(const SimpleVector& rhs);
    SimpleVector& operator=(const SimpleVector& rhs);

    SimpleVector(SimpleVector&& rhs) noexcept;
    SimpleVector& operator=(SimpleVector&& rhs) noexcept;

    friend void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept
    {
        using std::swap;

        swap(lhs.mSize, rhs.mSize);
        swap(lhs.pVec, rhs.pVec);
    }

    friend std::ostream& operator<<(std::ostream& os, const SimpleVector& vec)
    {
        os<<"vec size of "<<vec.mSize<<":\n";
        os<<"{";
        for (int i = 0; i < vec.mSize; ++i) {
            os<<*(vec.pVec + i)<< (i == vec.mSize -1 ?  "" : ", ");
        }
        os<<"}\n";

        return os;
    }

    auto operator==(const SimpleVector& rhs) const noexcept
    {
        if(mSize != rhs.mSize){
            return false;
        }

        for (int i = 0; i < mSize; ++i) {
            if(*(pVec + i) != *(rhs.pVec + i)){
                return false;
            }
        }

        return true;
    }
    auto operator!=(const SimpleVector& rhs) const noexcept
    {
        return !(*this == rhs);
    }
private:
    size_t mSize;
    int* pVec;
};

}//namespace simple
#endif //EXERCIS_SIMPLEVECTOR_H
