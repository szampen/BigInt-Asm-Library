CXX = g++
ASM = nasm
CXXFLAGS = -m64 -Wall -Iinclude
ASMFLAGS = -f elf64

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
INC_DIR = include

LIB_OBJS = $(OBJ_DIR)/BigInt.o $(OBJ_DIR)/BigInt_x64.o

TEST_BINS = test_main test_zero_copy

all: setup $(TEST_BINS)

setup:
	mkdir -p $(OBJ_DIR)

test_main: $(TEST_DIR)/test_main.cpp $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test_zero_copy: $(TEST_DIR)/test_zero_copy.cpp $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/BigInt.o: $(SRC_DIR)/BigInt.cpp $(INC_DIR)/BigInt.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/BigInt_x64.o: $(SRC_DIR)/BigInt_x64.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TEST_BINS)

.PHONY: all setup clean
