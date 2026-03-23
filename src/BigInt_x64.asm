section .text
    ; Memory functions
    global zero_data
    global copy_data

    ; BigInt methods
    global _ZN6BigInt3addEj
    global _ZN6BigInt8multiplyEj
    global _ZN6BigInt19divideWithRemainderEj

    ; Operators
    global _ZplRK6BigIntS1_
    global _ZmiRK6BigIntS1_

    ; Constructor call
    extern _ZN6BigIntC1Ej


; ============================================================================
; void zero_data(unsigned int* data, unsigned int size)
; RDI - array data
; RSI - size of array
; ============================================================================ 
zero_data:
    cld ; Set DF flag - registers will be incremented
    mov eax, 0 ; zeroing, so EAX to 0, because it is needed for STOSx
    mov ecx, esi ; REP requires count in ECX
    rep stosd ; repeat STOSD 'ECX' times
    ; STOSD - takes data from EAX to EDI (where the array is) and moves the EDI pointer by 4 bytes
    ret

; ============================================================================
; void copy_data(unsigned int * dest, unsigned int * src, unsigned int size)
; RDI - dest
; RSI - src
; RDX - n
; ============================================================================
copy_data:
    cld
    mov ecx, edx 
    rep movsd ; MOVSD - przenosi z ESI do EDI i przesuwa ESI oraz EDI o 4 bajty
    rep movsd ; repeat MOVSD 'ECX' times
    ; MOVSD - transfers data from ESI to EDI and moves the ESI and EDI pointers by 4 bytes
    ret

; ============================================================================
; int BigInt::add(unsigned int n)
; RDI - pointer to BigInt object
; RSI - number to add
; ret 0 - no overflow
; ret 1 - overflow
; ============================================================================
_ZN6BigInt3addEj:
   mov ecx, [rdi] ; BigInt size
   mov rax, [rdi + 8] ; Pointer to data[0] array
   
   add [rax], esi ; adding number to BigInt - because ESI is unsigned - 4 bytes
   jnc no_overflow ; If no overflow, end program
   ;CF = 0 => jump

   mov edx, 1 ; Array index counter

carry_loop:
    cmp edx, ecx ; index >= size, means oveflow
    jae overflow

    adc dword [rax + rdx * 4], 0 ; data[index] += 0 + CF - 
    jnc no_overflow ; If CF is cleared, end loop
    inc edx ; index++
    jmp carry_loop

no_overflow:
    mov rax, 0
    ret

overflow:
    mov rax, 1
    ret

; ============================================================================
; int BigInt::multiply(unsigned int n)
; RDI - pointer to BigInt object
; RSI - number to multiply
; ret 0 - no overflow
; ret 1 - overflow
; ============================================================================  
_ZN6BigInt8multiplyEj:
    mov ecx, [rdi] ; BigInt size
    mov r8, [rdi+8] ; pointer to the data[0] array

    xor r9d, r9d ; r9d - carry from previous iteration, initially 0
    xor r10d, r10d ; r10d - array index counter

mul_loop:
    cmp r10d, ecx
    jae test_carry

    mov eax, [r8 + r10 * 4] ; EAX = data[index]
    mul esi ; EDX:EAX = EAX * ESI

    add eax, r9d ; EAX += carry from previous iteration
    adc edx, 0 ; EDX += CF

    mov [r8 + r10 * 4], eax ; data[index] = result
    mov r9d, edx ; carry for next iteration = EDX (what didn't fit in 32 bits we carry to the next iteration)

    inc r10d ; index++
    jmp mul_loop

test_carry:
    test r9d, r9d
    je no_overflow

    jmp overflow

; ============================================================================
; int BigInt::divideWithRemainder(unsigned int n)
; RDI - pointer to BigInt object
; RSI - divisor
; ret - remainder of division
; ============================================================================  
_ZN6BigInt19divideWithRemainderEj:
    mov ecx, [rdi] ; size of BigInt
    mov r8, [rdi+8] ; pointer to the data[0] array

    xor edx, edx ; clear EDX before division
    dec ecx ; ECX to size - 1, so it's correctly indexed, going from the end

div_loop:
    cmp ecx, 0 ; if index < 0 => end of operations
    jl end_div

    mov eax, [r8 + rcx * 4] ; EAX = data[index]

    div esi ; EAX = EDX:EAX / ESI, EDX = EDX:EAX mod ESI - in EDX we will have the new remainder

    mov [r8 + rcx * 4], eax ; EAX = result of division

    dec ecx ; index--
    jmp div_loop

end_div:
    mov eax, edx ; result is the remainder of division, so we move EDX to EAX
    ret

; ============================================================================
; BigInt operator+ (const BigInt & a, const BigInt & b)
; RDI - pointer to the place, where the result should be created
; RSI - pointer to BigInt a
; RDX - pointer to BigInt b
; ============================================================================ 
_ZplRK6BigIntS1_
    enter 0,0

    ; ABI64 - those registers need to be preserved, because they can be changed by the constructor call
    push r12
    push r13
    push r14

    mov r12, rdi ; R12 = result address
    mov r13, rsi ; R13 = &a
    mov r14, rdx ; R14 = &b

    mov esi, [r13] ; ESI = a.size
    mov rdi, r12 ; RDI = result address
    call _ZN6BigIntC1Ej ; call BigInt constructor on result address - creating new BigInt object with size = a.size = b.size

    mov r8, [r12 + 8] ; R8 = result.data
    mov r9, [r13 + 8] ; R9 = a.data
    mov r10, [r14 + 8] ; R10 = b.data
    mov ecx, [r13] ; ECX = a.size = b.size

    xor r11d, r11d ; R11d - index, on which element of the array we are
add_loop:
    mov eax, [r9 + r11*4] ; EAX = a.data[i]
    adc eax, [r10 + r11*4] ; EAX += b.data[i] + CF (a.data[i] + b.data[i] + CF)     

    mov [r8 + r11*4], eax ; result.data[i] = (a.data[i] + b.data[i] + CF) 

    inc r11d ; index++
    dec ecx ; size --
    jnz add_loop ; if size != 0 => continue loop

end_add:    
    mov rax, r12 ; return result address in RAX - according to convention

    ; pop off the registers we pushed earlier to preserve their values
    pop r14
    pop r13
    pop r12

    leave
    ret

; ============================================================================
; BigInt operator- (const BigInt & a, const BigInt & b)
; RDI - pointer to the place, where the result should be created
; RSI - pointer to BigInt a
; RDX - pointer to BigInt b
; ============================================================================    
_ZmiRK6BigIntS1_
    enter 0,0

    push r12
    push r13
    push r14

    mov r12, rdi ; R12 = address of result
    mov r13, rsi ; R13 = &a
    mov r14, rdx ; R14 = &b

    mov esi, [r13] ; ESI = a.size
    mov rdi, r12 ; RDI = address of result
    call _ZN6BigIntC1Ej ; call BigInt constructor on result address - creating new BigInt object with size = a.size = b.size

    mov r8, [r12 + 8] ; R8 = result.data
    mov r9, [r13 + 8] ; R9 = a.data
    mov r10, [r14 + 8] ; R10 = b.data
    mov ecx, [r13] ; ECX = a.size = b.size

    xor r11d, r11d ; R11d - index, on which element of the array we are
sub_loop:
    mov eax, [r9 + r11*4] ; EAX = a.data[i]
    sbb eax, [r10 + r11*4] ; EAX -= b.data[i] - CF (a.data[i] - b.data[i] - CF)     

    mov [r8 + r11*4], eax ; result.data[i] = (a.data[i] - b.data[i] - CF)  

    inc r11d ; index++
    dec ecx ; size--
    jnz sub_loop ; if size != 0 => continue loop

end_sub:
    mov rax, r12 

    pop r14
    pop r13
    pop r12

    leave
    ret