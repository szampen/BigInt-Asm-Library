#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>

// C-style Assembly functions for memory management
extern "C"{
    void copy_data(unsigned int* dest, const unsigned int* src, unsigned int size);
    void zero_data(unsigned int* data, unsigned int size);
}

class BigInt {
    unsigned int size;
    unsigned int* data;

public:
    explicit BigInt(unsigned int size);
    BigInt(const BigInt& other);
    ~BigInt();
    BigInt& operator=(const BigInt& other);

    // Assembly implemented methods
    int add(unsigned int n);
    int multiply(unsigned int n);
    int divideWithRemainder(unsigned int n);

    BigInt& operator=(const char* number_str);
    friend std::ostream& operator<<(std::ostream& str, const BigInt& x);

    // Assembly implemented operators
    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
};

#endif