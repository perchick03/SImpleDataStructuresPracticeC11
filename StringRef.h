//
// Created by User on 6/30/2019.
//

#ifndef EXERCIS_STRINGREF_H
#define EXERCIS_STRINGREF_H

#include <ostream>
#include <algorithm> //std::swap


namespace simple
{

class StringRef
{
public:
    StringRef(const char* st = "");

    StringRef(const StringRef& rhs);
    StringRef& operator=(const StringRef& rhs);

    StringRef(StringRef&& rhs) noexcept;
    StringRef& operator==(StringRef&& rhs) noexcept;
    ~StringRef();

    bool operator==(const StringRef& rhs) const;
    bool operator!=(const StringRef& rhs) const;

    char& operator[] (size_t index);
    const char& operator[] (size_t index) const;

    size_t length() const;

    friend void swap(StringRef& lhs, StringRef& rhs) noexcept
    {
        using std::swap;
        swap(lhs.mSize, rhs.mSize);
        swap(lhs.mString, rhs.mString);
        swap(lhs.mRefCount, rhs.mRefCount);
    }
    friend std::ostream& operator<< (std::ostream& os, const StringRef& st)
    {
        return os;
    }
private:
    char* InitStringRef(const char* st);
private:
    size_t mSize;
    char* mString;
    mutable size_t mRefCount;
};
}//namespace simple
#endif //EXERCIS_STRINGREF_H
