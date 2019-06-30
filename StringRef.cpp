//
// Created by User on 6/30/2019.
//

#include "StringRef.h"
#include <cstring>
#include <cassert>

namespace simple
{


StringRef::StringRef(const char* st /*=""*/)
    :mSize(strlen(st))
    ,mString(InitStringRef(st))
    ,mRefCount(1)
{

}

StringRef::StringRef(const StringRef &rhs)
    :mSize(rhs.mSize)
    ,mString(rhs.mString)
    ,mRefCount(++rhs.mRefCount)
{

}

StringRef& StringRef::operator=(const StringRef &rhs)
{
    auto tmp_string(rhs);

    swap(*this, tmp_string);

    return *this;
}

StringRef::StringRef(StringRef &&rhs) noexcept
{
    swap(*this, rhs);
}

StringRef &simple::StringRef::operator==(StringRef &&rhs) noexcept {
    swap(*this, rhs);

    return *this;
}

StringRef::~StringRef() {
    if(--mRefCount == 0)
    {
        delete[] mString;
    }
}

bool StringRef::operator==(const StringRef &rhs) const
{
    return !strcmp(mString, rhs.mString);
}

bool StringRef::operator!=(const StringRef &rhs) const
{
    return !(*this == rhs);
}

//giving away a reference to internal char can't be shared.
char& StringRef::operator[](size_t index)
{
    assert(index < mSize);
    if(mRefCount > 1)
    {
       --mRefCount;
       mString = InitStringRef(mString);
    }
    return mString[index];

}

const char& StringRef::operator[](size_t index) const 
{
    return const_cast<StringRef*>(this)->operator[](index);
}

size_t StringRef::length() const 
{
    return mSize;
}


char* StringRef::InitStringRef(const char *st)
{
    mString = new char[mSize + 1];
    strncpy(mString, st, mSize);
    mString[mSize] = '\0';

    return mString;
}


}//namespace simple