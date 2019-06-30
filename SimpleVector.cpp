//
// Created by User on 6/26/2019.
//

#include "SimpleVector.h"
namespace simple
{


SimpleVector::SimpleVector(size_t size /* = 0*/)
    :mSize(size), pVec(new int[size])
{

}

SimpleVector::~SimpleVector() {
    mSize = 0;
    delete[] pVec;
    pVec = nullptr;
}

SimpleVector::SimpleVector(const SimpleVector& rhs): SimpleVector(rhs.mSize) {
    std::copy(rhs.pVec, rhs.pVec + mSize, pVec);
}

SimpleVector& SimpleVector::operator=(const SimpleVector& rhs) {
    auto tmp{rhs};

    swap(*this, tmp);
    return *this;
}

SimpleVector::SimpleVector(SimpleVector&& rhs) noexcept
{
    swap(*this, rhs);
    rhs.mSize = 0;
    rhs.pVec = nullptr;
}

SimpleVector &SimpleVector::operator=(SimpleVector&& rhs) noexcept {
    swap(*this, rhs);
    rhs.mSize = 0;
    rhs.pVec = nullptr;
    return *this;
}

SimpleVector::SimpleVector(const std::initializer_list<int> &il): SimpleVector(il.size()) {
    std::copy(il.begin(), il.end(), pVec);
}


}//namespace simple