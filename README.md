# The Monty Language
Monty 0.98 is a scripting language that is first compiled into Monty byte codes (just like Python). It relies on a unique stack, with specific instructions to manipulate it. The goal of this project is to create an interpreter for Monty ByteCodes files.

## Monty byte code files
Files containing Monty byte codes have the `.m` extension, but this is not required by the specification of the language and any extension can be used. There is not more than one instruction per line. There can be any number of spaces before or after the opcode and its argument. Monty byte code files can also contain blank lines (empty or made of spaces only), and any additional text after the opcode or its required argument is not taken into account. For example, the following is valid Monty byte code:
```
push 0
push 1

push 2
  push 3
                   pall    
push 4
    push 5    
      push    6        
pall
```

## Allowed opcodes
The following are valid Monty opcodes:
- `push`: pushes an element to the stack
- `pall`: prints all the values on the stack, starting from the top of the stack
- `pint`: prints the value at the top of the stack, followed by a new line
- `pop`: removes the top element of the stack
- `swap`: swaps the top two elements of the stack
- `add`: adds the top two elements of the stack
- `nop`: doesn’t do anything
- `sub`: subtracts the top element of the stack from the second top element of the stack
- `div`: divides the second top element of the stack by the top element of the stack
- `mul`: multiplies the second top element of the stack with the top element of the stack
- `mod`: computes the remainder of the division of the second top element of the stack by the top element of the stack
- `pchar`: prints the char at the top of the stack, followed by a new line. An error message is printed if the value is not in the ASCII table or if the stack if empty
- pstr: prints the string starting at the top of the stack, followed by a new line. The integer stored in each element of the stack is treated as the ascii value of the character to be printed. The string stops when the stack is over, the value of the element is 0, or the value of the element is not in the ASCII table. A newline is printed if the stack is empty
- rotl: rotates the stack to the top. The top element of the stack becomes the last one, and the second top element of the stack becomes the first one
- rotr: rotates the stack to the bottom. The last element of the stack becomes the top element of the stack

**NOTE**: For binary opcodes with a return value, e.g. `add` and `sub`, the result is stored in the second top element of the stack, and the top element is removed. The stack will therefore be one element shorter after the opcode is executed and result will be at the top of the stack.

## Usage
Monty is designed to work on GNU/Linux platforms.
1. First compile the program using the compilation script:
`./compile`
2. Execute a Monty bytecode file:
```
./monty file-with-monty-bytecode.m
```

## Errors
The monty program runs the bytecodes line by line and stops if it encounters an error. The program fails and prints an error message if:
- the user does not give any file or gives more than one argument to the program
- for any reason, it’s not possible to open the file
- the file contains an invalid instruction. Program execution will stop at the invalid instruction and the resulting error message will show the line number that caused the error.
- the program runs out of memory

In case of any of the above, the program exits with the status `EXIT_FAILURE`. The value of this exit status is defined in the C standard library and its value is 1 on most systems.

## Bugs
Monty does not check for integer underflow or overflow. The program behaviour will be undefined in these two scenarios.
