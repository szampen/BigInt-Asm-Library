#include "BigInt.h"
#include <iostream>

void run_tests(){
    std::cout << "Test 1: String Parsing & Basic Addition" << std::endl;
    BigInt a(5);
    a = "1000";
    std::cout << "Start: " << a << std::endl;
    a.add(234);
    std::cout << "After add(234): " << a << std::endl;  
    a.multiply(2);
    std::cout << "After multiply(2): " << a << std::endl;  
    std::cout << "Expected result: 2468" << std::endl << std::endl;


    std::cout << "Test 2: Large Division & Remainder" << std::endl;
    BigInt b(10);
    b = "10000000000"; 
    b.multiply(5);
    std::cout << "After multiply(5): " << b << std::endl;  
    unsigned int r = b.divideWithRemainder(7);
    std::cout << "Result: " << b << " remainder: " << r << std::endl;  
    std::cout << "Expected result: 7142857142 remainder 6" << std::endl << std::endl;


    std::cout << "Test 3: Multiplication in a loop & Assignment from String" << std::endl;
    BigInt c(10);
    c = "100";
    for(int i = 0; i < 5; i++){
        c.multiply(5);
        std::cout << "Iteration " << i+1 << ": " << c << std::endl; 
    }
    std::cout << "Expected result: 312500" << std::endl << std::endl;


    std::cout << "Test 4: Huge Strings Assignment" << std::endl;
    BigInt d(5);
    d = "999999999999";
    std::cout << "Assigned: 999999999999" << std::endl;
    std::cout << "Output:   " << d << std::endl << std::endl;


    std::cout << "Test 5: Overflow addition" << std::endl;
    BigInt h(5), i(5);
    h = "999999999"; 
    i = "1";
    
    BigInt j = h + i;
    
    std::cout << h << " + " << i << " = " << j << std::endl;
    std::cout << "Expected result: 1000000000" << std::endl << std::endl; 


    std::cout << "Test 6: Subtraction with borrow" << std::endl;
    BigInt k(5), l(5);
    k = "1000000000";  // 10^9
    l = "1";
    
    BigInt m = k - l;
    
    std::cout << k << " - " << l << " = " << m << std::endl;
    std::cout << "Expected result: 999999999" << std::endl << std::endl; 


    std::cout << "Test 7: ADC operation" << std::endl;
    BigInt n(10), o(10);
    n = "123456789012345";
    o = "987654321098765";
    
    BigInt p = n + o;
    
    std::cout << n << " + " << o << " = " << p << std::endl;
    std::cout << "Expected result: 1111111110111110" << std::endl << std::endl; 
    

    std::cout << "Test 8: SBB operation" << std::endl;
    BigInt z(10), s(10);
    z = "987654321098765";
    s = "123456789012345";
    
    BigInt q = z - s;
    
    std::cout << z << " - " << s << " = " << q << std::endl;
    std::cout << "Expected result: 864197532086420" << std::endl << std::endl;      


    std:: cout << "Test 9: Chained Operations" << std::endl;
    BigInt e(5), f(5), g(5);
    e = "1000";
    f = "2000";
    g = "500";
    
    BigInt result = (e + f) - g;
    
    std::cout << "(" << e << " + " << f << ") - " << g << " = " << result << std::endl;
    std::cout << "Expected result: 2500" << std::endl << std::endl; 


    std::cout << "Test 10: Chained Operations" << std::endl;
    BigInt t(5), u(5), w(5);
    t = "100";
    u = "200";
    w = "300";
    
    BigInt v = t + u + w;
    
    std::cout << t << " + " << u << " + " << w << " = " << v << std::endl;
    std::cout << "Expected result: 600" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  BIGINT x64 ASSEMBLY HYBRID TEST SUITE " << std::endl;
    std::cout << "========================================" << std::endl << std::endl;
    
    run_tests();
    
    std::cout << "========================================" << std::endl;
    std::cout << "  ALL TESTS FINISHED                    " << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}