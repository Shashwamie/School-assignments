#ifndef FILTER_OUTPUT_H
#define FILTER_OUTPUT_H

#include "Output.h"
#include "DecoratorBase.h"

template <typename T>
class FilterOutput : public DecoratorBase<T>{
    Output<T> *localOutput;
public:
    FilterOutput(Output<T> *output) : localOutput(output){}

    void write(const T& t){
        //localOutput.write(t);
    }
    void writeString(const std::string& s){
        localOutput->writeString("Filter " + s);
    }
};

#endif
