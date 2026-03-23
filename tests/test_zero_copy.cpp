#include "BigInt.h"
#include <cstdio>

// Helper function to display the array contents
void display_array(const char* label, unsigned int* tab, unsigned int n) {
    printf("%s: ", label);
    for (unsigned int i = 0; i < n; i++) {
        printf("%u ", tab[i]);
    }
    printf("\n");
}

// Test 1: Basic copying
void test1_basic_copy() {
    printf("=== TEST 1: Basic Copying ===\n");
    unsigned int source[] = {1, 2, 3, 4, 5};
    unsigned int target[5] = {0, 0, 0, 0, 0};
    
    printf("Before:\n");
    display_array("  Source", source, 5);
    display_array("  Target", target, 5);
    
    copy_data(target, source, 5);
    
    printf("After copy_data(target, source, 5):\n");
    display_array("  Source", source, 5);
    display_array("  Target", target, 5);
    
    printf("\nExpected: Target should be {1, 2, 3, 4, 5}\n");
    printf("Result: %s\n\n", 
           (target[0]==1 && target[1]==2 && target[2]==3 && target[3]==4 && target[4]==5) ? "✓ PASS" : "✗ FAIL");
}

// Test 2: Partial copying
void test2_partial_copy() {
    printf("=== TEST 2: Partial Copying ===\n");
    unsigned int source[] = {10, 20, 30, 40, 50};
    unsigned int target[5] = {99, 99, 99, 99, 99};
    
    printf("Before:\n");
    display_array("  Source", source, 5);
    display_array("  Target", target, 5);
    
    copy_data(target, source, 3);  // Copy only first 3 elements
    
    printf("After copy_data(target, source, 3):\n");
    display_array("  Source", source, 5);
    display_array("  Target", target, 5);
    
    printf("\nExpected: Target should be {10, 20, 30, 99, 99}\n");
    printf("Result: %s\n\n", 
           (target[0]==10 && target[1]==20 && target[2]==30 && target[3]==99 && target[4]==99) ? "✓ PASS" : "✗ FAIL");
}

// Test 3: Basic zeroing
void test3_basic_zeroing() {
    printf("=== TEST 3: Basic Zeroing ===\n");
    unsigned int buffer[] = {100, 200, 300, 400, 500};
    
    printf("Before:\n");
    display_array("  Buffer", buffer, 5);
    
    zero_data(buffer, 5);
    
    printf("After zero_data(buffer, 5):\n");
    display_array("  Buffer", buffer, 5);
    
    printf("\nExpected: Buffer should be {0, 0, 0, 0, 0}\n");
    printf("Result: %s\n\n", 
           (buffer[0]==0 && buffer[1]==0 && buffer[2]==0 && buffer[3]==0 && buffer[4]==0) 
           ? "✓ PASS" : "✗ FAIL");
}

// Test 4: Partial zeroing
void test4_partial_zeroing() {
    printf("=== TEST 4: Partial Zeroing ===\n");
    unsigned int buffer[] = {111, 222, 333, 444, 555, 666};
    
    printf("Before:\n");
    display_array("  Buffer", buffer, 6);
    
    zero_data(buffer, 4);  // Zero only first 4 elements
    
    printf("After zero_data(buffer, 4):\n");
    display_array("  Buffer", buffer, 6);
    
    printf("\nExpected: Buffer should be {0, 0, 0, 0, 555, 666}\n");
    printf("Result: %s\n\n", 
           (buffer[0]==0 && buffer[1]==0 && buffer[2]==0 && buffer[3]==0 
            && buffer[4]==555 && buffer[5]==666) ? "✓ PASS" : "✗ FAIL");
}

// Test 5: Large values copying
void test5_large_values() {
    printf("=== TEST 5: Large Unsigned Int Values ===\n");
    unsigned int source[] = {0xFFFFFFFF, 0x80000000, 0x12345678, 0xDEADBEEF};
    unsigned int target[4] = {0, 0, 0, 0};
    
    printf("Before:\n");
    display_array("  Source", source, 4);
    display_array("  Target", target, 4);
    
    copy_data(target, source, 4);
    
    printf("After copy_data(target, source, 4):\n");
    display_array("  Source", source, 4);
    display_array("  Target", target, 4);
    
    printf("\nExpected: Target = {4294967295, 2147483648, 305419896, 3735928559}\n");
    printf("Result: %s\n\n", 
           (target[0]==0xFFFFFFFF && target[1]==0x80000000 && target[2]==0x12345678 && target[3]==0xDEADBEEF) 
           ? "✓ PASS" : "✗ FAIL");
}

// Test 6: Zeroing with n=0
void test6_zero_empty() {
    printf("=== TEST 6: Zeroing with n=0 (Edge Case) ===\n");
    unsigned int buffer[] = {777, 888, 999};
    
    printf("Before:\n");
    display_array("  Buffer", buffer, 3);
    
    zero_data(buffer, 0);  // Should do nothing
    
    printf("After zero_data(buffer, 0):\n");
    display_array("  Buffer", buffer, 3);
    
    printf("\nExpected: Buffer unchanged {777, 888, 999}\n");
    printf("Result: %s\n\n", 
           (buffer[0]==777 && buffer[1]==888 && buffer[2]==999) ? "✓ PASS" : "✗ FAIL");
}

// Test 7: Combined - Copy then Zero
void test7_combined_flow() {
    printf("=== TEST 7: Combined Flow (Copy + Zero) ===\n");
    unsigned int source[] = {11, 22, 33, 44, 55};
    unsigned int target[5] = {0, 0, 0, 0, 0};
    
    printf("Step 1 - Copying:\n");
    display_array("  Source before", source, 5);
    display_array("  Target before", target, 5);
    
    copy_data(target, source, 5);
    
    display_array("  Target after ", target, 5);
    
    printf("\nStep 2 - Zeroing source:\n");
    display_array("  Source before", source, 5);
    
    zero_data(source, 5);
    
    display_array("  Source after ", source, 5);
    display_array("  Target (remains)", target, 5);
    
    printf("\nExpected: Source={0,0,0,0,0}, Target={11,22,33,44,55}\n");
    printf("Result: %s\n\n", 
           (source[0]==0 && source[4]==0 && target[0]==11 && target[4]==55) ? "✓ PASS" : "✗ FAIL");
}

int main() {
    printf("╔════════════════════════════════════════════╗\n");
    printf("║  LOW-LEVEL STRING OPERATIONS TESTS (ASM)   ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    test1_basic_copy();
    test2_partial_copy();
    test3_basic_zeroing();
    test4_partial_zeroing();
    test5_large_values();
    test6_zero_empty();
    test7_combined_flow();
    
    printf("╔════════════════════════════════════════════╗\n");
    printf("║  ALL ASM CORE TESTS FINISHED               ║\n");
    printf("╚════════════════════════════════════════════╝\n");
    
    return 0;
}