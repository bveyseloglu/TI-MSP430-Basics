## TI-MSP430-Basics
Basic tutorials for Texas Instruments MSP430FR5969, both Assembly and C. These are my laboratory work for Microprocessors I course.

## Development Environment
Codes were tested on Code Composer Studio 7.

## Lab Tasks
### 1. Register Operations
1 – Load the number 123 to R9. Move this value to R7./
2 – Load the number 0x4400 to R5. Load the number 99 to R6. Store the contents of R6 to the memory at the address in R5./
3 – Continuing from 2, load the contents of the memory at the address 0x4400 to R5./
4 – Starting from the address 0x4400, store the numbers 11, 22, 33, 44 to the memory as bytes. Mind the endian ordering./
5 – Continuing from 4, add the numbers stored to the memory and store the result in R6./

### 2. Memory Operations and Branches
1 – Using assembler directives, create an array in the memory, and initialize it with the numbers below (use .word):
9712, 2454, 1275, 3312, 4243, 2395, 4387, 12236, 9454, 32221
2 – Find the number of elements that are greater than 10000 in the array created in step 1 and store the result in R9.
3 – Create a 20 byte-long uninitialized section in the memory (use .bss).
4 – Fill the buffer created in step 3 with even numbers starting from 2. Numbers will be stored as words.

### 3. Memory Operations
#### Part 1
1 – Using the assembler directives, store the 64-bit number below in the memory.
0x2be51cf06549a0d1
2 – Read the number given in step 1 from the memory, shift left once, overwrite the result.

#### Part 2
1– Using the assembler directives, store the date to the memory as three words.
e.g.: 6, 3, 18 (day, month, year)
2 – Using the representation below, format this date into a single word. Store the result in R9.

| Day (1-31) | Month (1-12) | Year (00-99) |
|------------|--------------|--------------|
| 5 bits     | 4 bits       | 7 bits       |

### 4. Subroutines and Stack
Suppose we want to implement an addition function to perform the following: c=a+b
The terms (a,b) are to be passed by value. The sum (c) is to be passed by reference. This can be implemented in C as such:
void addition(int a, int b, int* c)
{
*c = a + b;
}

Implement this in ARM assembly as a subroutine, and use it to add two numbers.
* (a,b,c) are word-sized.
* Your subroutine should not change register or memory contents (except for c).
* Upon returning from the subroutine, SP should remain unchanged.
* All arguments are passed by stack.

### 5. Input-Output
Do some basic I/O stuff by using LEDs and switches.

### 6. Seven Segment Application
Write a C program that displays digits starting from 0 up to 9 on the seven-segment display. Each digit will be displayed for 1 second. Once the count reaches 9, it will loop back to 0 and continue from there.

### 7. Seven Segment Application 2
Set up the circuit from 6. Implement the same program in C using timer interrupts. Instead of using 1 second-long delays, set up a timer interrupt that gets activated every second.

### 8. Temperature Sensor
Read temperature from internal sensor.

## License
Licensed under MIT License.
