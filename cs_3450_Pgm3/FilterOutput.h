#ifndef FILTER_OUTPUT_H
#define FILTER_OUTPUT_H

#include <cctype>
#include <string>
#include "Output.h"
#include "DecoratorBase.h"

template <typename T>
class FilterOutput : public DecoratorBase<T>{
    Output<T> *localOutput;
    std::string selection;
public:
    FilterOutput(Output<T> *output, std::string selection) : localOutput(output), selection(selection){}

    void write(const T& t){
        if(selection == "1" && has_num(t)){
            localOutput->write(t);
        }
        else if(selection == "2" && has_at(t)){
            localOutput->write(t);
        } 
        else if(selection == "3" && has_octo(t)){
            localOutput->write(t);
        } 
        else if(selection == "4" && less_than_50(t)){
            localOutput->write(t);
        } 
        else if(selection == "5" && has_python(t)){
            localOutput->write(t);
        }   
    }
    void writeString(const std::string& s){}

    // function determines if line contains a digit
    bool has_num(T t){
        std::string x = t;
        char arr[x.length()+1];

        bool containsDigit = false;
        for(int i = 0; i < x.length(); i++){
            arr[i] = x.at(i);
            if(isdigit(arr[i])){
                containsDigit = true;
                break;
            }
        }
        return containsDigit;
    }

    // function determines if line contains an asperand (@)
    bool has_at(T t){
        std::string x = t;
        char arr[x.length()+1];

        bool containsAt = false;
        for(int i = 0; i < x.length(); i++){
            arr[i] = x.at(i);
            if(arr[i] == '@'){
                containsAt = true;
                break;
            }
        }
        return containsAt;
    }

    // function determines if line contains an octothorpe (#)
    bool has_octo(T t){
        std::string x = t;
        char arr[x.length()+1];

        bool containsOcto = false;
        for(int i = 0; i < x.length(); i++){
            arr[i] = x.at(i);
            if(arr[i] == '#'){
                containsOcto = true;
                break;
            }
        }
        return containsOcto;
    }

    // function determines if line has less than 50 characters
    bool less_than_50(T t){
        std::string x = t;
        return (t.length() < 50);
    }

    // function determines if line contains reference to python
    bool has_python(T t){
        std::string str = t;
        std::string python = "Python";
        if(str.find(python) != std::string::npos){
            return true;
        }
        return false;
    }
};

#endif
