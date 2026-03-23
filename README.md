# BigInt-Asm: High-Performance Arbitrary Precision Library

A hybrid C++/x86-64 Assembly library designed for high-efficiency arithmetic on integers of arbitrary size.

## Key Technical Highlights
- **Manual Memory Management:** Implements the **Rule of Three** (Destructor, Copy Constructor, Copy Assignment) to manage raw memory on the heap.
- **Assembly Kernels:** Critical paths for addition and subtraction are written in **x86-64 Assembly**, utilizing the CPU's Carry Flag (CF). 
- **System V ABI Compliance:** Seamlessy passes data between C++ and Assembly using standard register conventions (`RDI`,`RSI`,`RDX`,`RCX`).
- **Optimized Data Layout:** Stores numbers as a contiguous array of 64-bit blocks (quadwords), maximizing cache efficiency and CPU world alignment.

## Project Structure
```text
.
├── include/
│   └── BigInt.h          # Class declarations & External ASM signatures
├── src/
│   ├── BigInt.cpp        # C++ logic, memory management & operator wrappers
│   └── BigInt_x64.asm    # Optimized x86-64 assembly implementation
├── tests/
│   ├── test_main.cpp     # Unit tests for BigInt operations
│   └── test_asm_core.cpp # Direct testing of assembly primitives
├── Makefile              # Automated build system
└── README.md
```

## Low-Level Implementation Details

### The Carry Ripple (ASM)
Unlike standard C++ which hides CPU status flags, this library directly utilizes the `ADC` (addition with carry) and `SBB` (subtraction with borrow) instructions. This allows $O(N)$ time complexity for addition/subtraction, where $N$ is the number of 64-bit blocks.

### Memory Architecture

Numbers are represented as:

$$V = \sum_{i=0}^{n-1} d_i \cdot (2^{64})^i$$

where $d_i$ is a 64-bit digit stored in the heap. This allows the library to handle numbers limited only by the available RAM.

## Prerequisites
- **NASM** 
- **GCC/G++** 
- **GNU Make**

## Build & Run
1. **Clone the repository**
    ```bash
    git clone https://github.com/szampen/BigInt-Asm-Library.git
    cd BigInt-Asm-Library
    ```

2. **Build the project**
    ```bash
    make
    ```

3. **Run core tests**
    ```bash
    ./test_main
    ./test_zero_copy
    ```

