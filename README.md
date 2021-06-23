# The-C-Programming-Language-Exercises
A Repo containing my exercise solutions for "The C Programming Language" - by Brian Kernighan and Dennis Ritchie

You will find that this Repo is structured according the chapters in the book:
 - Chapter 1 (A Tutorial Introduction)
 - Chapter 2 (Types, Operators, and Expressions)
 - Chapter 3 (Control Flow)
 - Chapter 4 (Functions and Program Structure)
 - Chapert 5 (Pointers and Arrays)
 - Chapter 6 (Structures)
 - Chapter 7 (Input & Output)

# By Chapters
## Chapter 1 (A Tutorial Introduction):
- Compiling and printing your first "hello world" + string constants (hardcoded characters enclosed in quotes " ")
- Variables and Arithmetic expressions (Temperature conversion table)
- For loops (init; condition; expression)
- Symbolic constants `#define` conducts replacement
- Character IO `getchar()` and `putchar(c)` (file copying, character counting, line counting, word counting)
- Arrays subscript operator []
- Functions callable operator () & function prototypes
- Arguments--Call by Value
- Character arrays (Strings) and `'\0'` terminator value

## Chapter 2 (Types, Operators, and Expressions):
- Variable naming conventions (lowercase for variable names and upper case for symbolic constants)
- Data types and sizes __(Read notes)__
- Constants long constants have terminal `L` and unsigned constants have terminal `U`. enum constant
- Declarations must be done before use! Declaration != Definition. Initializers must be static. An explicitly initialized variable is initialized everytime the function/block is entered. `external/static` is initializes as zero.
- Arithmetic operators: associate left to right
- Relational and Logical operators: Relational have less precedence than arithmetic operators. Expressions connected by logical operators evaluate left to right
- Type conversions __(Read notes)__
- Increment and Decrement Operators, postfix/prefix ++/--
- Bitwise operators ~, &, |, ^, <<, >>, -`
- Assignment Operators and Expressions
- Conditional Expressions
- Order of Evaluation

## Chapter 3 (Control Flow)
> To be done
## Chapter 4 (Functions and Program Structure)
> To be done
## Chapert 5 (Pointers and Arrays)
> To be done
## Chapter 6 (Structures)
- Basic structure syntax
- How to use structures in functions
- Structure arrays `struct example[10]`
- Pointers to structures and "`->`" syntax to access to members
- Self referential structures (Tree structures)
- Table lookup (Hashing and Linked list structures)
- `typedef` keyword
- `union` keyword
- Bit-fields (Used for packing objects in a single word, E.g. Defining a set of masks alternatively fields can be used which are structs that have members which are explicitly defined unsigned/signed ints and with : < bitsize >)
## Chapter 7 (Input & Output)
> To be done

1. **Standard input and output**: The C standard library implements a model to deal with I/O in the form of a text stream which are lines of text separated by a newline character. If the system doesn't work this way, the library makes it appear as though it does. Most systems use use indirection operators `< >` and piping `|`. It is important to understand the nuance of these two system functions. The <> in `#define <stdlib.h>` tells UNIX systems to look into /usr/include to find these header files.
2. **Formatted Output - Printf**: printf is a library function that formats input based on your specification and passes it to standard output. There is a plethora of formatting functionality built into print. It can be found on (pg 154). Most useful to know is that a minus sign `%-` means left adjustment. A number `%5` determines the minimum field width of the output (used mostly for padding). A period separates the width from the precision of the output `%.3`. 
3. **Variable-Length Argument Lists**: elipses used in function declaration indicate that the function can take a variable number of arguments. e.g. `int myfunc(int, ...)`. In order to access the variable list, the C standard library provides the type va_list in <stdarg.h>. [Exercise: minprintf]
```
#include <stdarg.h>

int myfunc(int x, ...)
{
    va_list ap;
    va_start(ap, x);    /* x is the last argument before va_list */
    
    int i = va_arg(ap, int); /* 2nd argument is the desired type */

}
```
4. **Formatted Input - Scanf**: It may also be convenient to get format specific input if you expect a certain input. Scanf works in the opposite fashion from printf whereby the input format is specified and by the user and stored into the addresses provided by the user when describing the format. [Exercise: minscanf & postfix calculator]
5. **File Access**: So far our c programs have been mainly interacting with stdin and stdout which are automatically opened and provided to us by the O.S in the form of file descriptors when the process starts. We can interact with other files by opening them with `FILE *fopen(char *name, char *mode)`. FILE is a structure which contains information about the buffer, permissions, location, etc. Always close opened files because most O.S. put limits on how many opened files a process can have simultaneously. At the same time, closing also flushes the buffer. [cat example]
6. **Error Handling - Stderr and Exit**: There is a third file descriptor provided by the O.S. which is stderr. Stderr is connected to your screen but can be redirected into log files instead. The reason for this is to separate your errors from your output. Instead of using return statements, more complex programs can benefit from using `exit(expr)`. Whilst this is semantically the same as `return expr`, using the exit function however has the benefit that it can be called from other functions. Conventionally, exit status's of 0 means it normal termination wheras non-zero is abnormal status's
7. **Line Input and Output** - 

# Additional Notes

**Function declaration vs definition**
> to do

**Data types:**
- A word is a fixed size of data that a computer processor is able to handle as a unit. It is machine dependent such as having 32/64 bit machines that indicate the word size that it is able to process at one go
- The main 4 data types are `char(1), int(2/4), float(4), double(8)`
- An int is either a 2/4 bytes long dependent on the machine.
- There are qualifiers such as short/long which tell compiler how to intepret the data sizes. Again a short and long is machine dependent. However the following rules apply. short <= int <= long
- There are qualifiers `signed` and `unsigned` which alters the range of values taken by the data type. E.g. a char is 8bits long which translates to 256 different representations. An unsigned char ranges from 0-255 whilst a signed char ranges from -128 - 127
- The way the processor treats signed datatypes is by using the (Twos complement machine) which finds the negative representation of a binary number as the inverted bits + 1. Therefore in a 3 bit system, 2 : 010 ~ inverted = 101 -> +1 = 110 : -2

**Differences between an expression & statement:**
- Expressions include variables, operators, callables, subscritors and anything that evaluates to some value.
- Statements on the other hand are generally a collection of expressions but may also include control flow, etc. Expressions are statements but the same is not true vice versa.

**Type Conversions**:
- As a general rule of thumb, narrower types get converted to wider types. Converting in the opposite is prone to information lost but are not illegal.
- When you implicitly/explicitly cast a type to a different one, it produces a new value but the original value and it's type is unchanged.