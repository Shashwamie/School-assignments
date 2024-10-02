#ifndef NUMBERED_OUTPUT_H
#define NUMBERED_OUTPUT_H

#include "Output.h"
#include "DecoratorBase.h"
#include <string>
#include <iomanip>

template <typename T>
class NumberedOutput : public DecoratorBase<T>{
    Output<T> *localOutput;
    int count = 0;
public:
    NumberedOutput(Output<T> *output) : localOutput(output){}

    void write(const T& t){
        count++;
        std::string countString = std::to_string(count);
        localOutput->write(countString + ": ");
        localOutput->write(t);
    }
    void writeString(const std::string& s){}
};

#endif
