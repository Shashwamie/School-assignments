#ifndef TEE_OUTPUT_H
#define TEE_OUTPUT_H

#include "Output.h"
#include "DecoratorBase.h"

template <typename T>
class TeeOutput : public DecoratorBase<T>{
    Output<T> *localOutput;
    std::ostream& localSink;
public:
    TeeOutput(Output<T> *output, std::ostream& newStream) : localOutput(output), localSink(newStream){}

    void write(const T& t){
        localOutput->write(t);
        localSink << t;
    }
    void writeString(const std::string& s){
        localOutput->writeString("Tee " + s);
    }
};

#endif
