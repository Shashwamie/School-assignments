#ifndef DECORATOR_BASE_H
#define DECORATOR_BASE_H

#include "Output.h"
#include <iostream>

template<typename T>
class DecoratorBase : public Output<T> {
public:
    virtual void write(const T& t) = 0;
    virtual void writeString(const std::string& s) = 0;
};

#endif
