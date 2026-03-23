#include "BigInt.h"
#include <algorithm>

// Constructor
BigInt::BigInt(unsigned int size) : size(size), data(new unsigned int[size]){
    zero_data(data, size);
}

// Copy Constructor
BigInt::BigInt(const BigInt& other) : size(other.size), data(new unsigned int[other.size]){
    copy_data(data, other.data, size);
}

// Assignment Operator
BigInt& BigInt::operator=(const BigInt& other) {
    if (size != other.size){
        unsigned int* tmp = new unsigned int[other.size];
        delete[] data;
        size = other.size;
        data = tmp;
    }
    copy_data(data, other.data, size);
    return *this;
}

// Destructor
BigInt::~BigInt() {
    delete[] data;
}

// Assignment from string
BigInt& BigInt::operator=(const char* number_str) {
    zero_data(data, size);

    while(*number_str != '\0'){
        unsigned int digit = *number_str - '0';
        multiply(10);
        add(digit);
        number_str++;
    }
    return *this;
}

// Output stream operator
std::ostream& operator<<(std::ostream& str, const BigInt& x) {
    bool is_zero = true;
    for(unsigned int i = 0; i < x.size; i++){
        if(x.data[i] != 0){
            is_zero = false;
            break;  
        }
    }

    if(is_zero){
        str << "0";
        return str;
    }

    BigInt temp = x;
    std::string result;

    while(true){
        unsigned int digit = temp.divideWithRemainder(10);
        result += ('0' + digit);

        is_zero = true;
        for(unsigned int i = 0; i < temp.size; i++){
            if(temp.data[i] != 0){
                is_zero = false;
                break;
            }
        }

        if(is_zero){
            break;
        }
    }

    std::reverse(result.begin(), result.end());
    str << result;
    return str;