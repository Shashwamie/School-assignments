#ifndef BRACKET_OUTPUT_H
#define BRACKET_OUTPUT_H

#include "Output.h"
#include "DecoratorBase.h"

template <typename T>
class BracketOutput : public DecoratorBase<T>{
    Output<T> *localOutput;
public:
    BracketOutput(Output<T> *output) : localOutput(output){}

    void write(const T& t){
        localOutput->write("[" + t.substr(0, t.length()-1) + "]\n");
    }
    void writeString(const std::string& s){}
};

#endif
