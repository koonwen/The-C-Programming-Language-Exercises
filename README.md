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
6. **Error Handling - Stderr and Exit**: There is a third file descriptor provided by the O.S. which is stderr. Stderr is connected to your screen but can be redirected into log files instead. The reason for this is to separate your errors from your output. Instead of using return statements, more complex programs can benefit from using `exit(expr)`. Whilst this is semantically the same as `return expr` in "main", using the exit function however has the benefit that it can be called from other functions and terminates the entire program. Conventionally, exit status's of 0 means it normal termination wheras non-zero is abnormal status's
7. **Line Input and Output** - The standard library implements a similar function to `getline` known as `gets` except it reads from a stream. Take note that library functions with "f___" are equivalent to those without. The f portion just allows you to specify which file or stream to take input or channel output. Those without the f generally either take from stdin write to stdout. It is useful to keep in mind that these library functions don't provide very good return values. For e.g. `fgets` returns NULL if either an error or EOF is encountered. To get over this this problem, there is an additional function provided `feof(FILE *)` and `ferror(FILE *)` that we can use to test the status of the file pointer.
8. **Miscellaneous Functions** - `ungetc` only gurantees 1 character of pushback. You can execute system programs from within c programs by using the function `system(char *s)`. The difference between calloc and malloc is that calloc initializes storage to 0.

## Chapter 8 (The Unix System Interface):
Summary : In order to allow our programs to gain access to the O.S services, the Unix operating system provides a set of system functions(system calls) which can be used by user programs to gain access to system resources.
1. **File descriptors** - In Unix, everything is represented as a file. The reason for this is that it establishes a uniform way of interacting with the various resources in a machine. Generally when performing a read/write operation to a file, the file must first must be open. The O.S, is responsible for providing the file descriptor (After checking permissions, etc.) which is the entry point to manipulate the file. The file descriptor is a small non-negative integer and is analogour to the file pointer described in the standard library. We learnt that stdin, stdout and stderr are in fact the file decriptors {0,1,2} opened by the O.S. whenever a program is run. All information about the opened file is maintained by the system. The user program only interacts with the file descriptor.
2. **Low Level I/O - Read and Write** - System calls are in effect the entry point in which user programs can use the hardware of the device. Thus far we have been using standard library I/O functions such as `getchar` and `putchar` but these functions are built using system calls. I.e. getchar(), is just pre-defined the read operation on the file descriptor 0 (which corresponds to stdin, by default the keyboard) with a size of 1 byte (because a char is 1 byte). However, do take note that there are other implementations of getchar that instead take more input but buffers them and hands out the char input one at a time.
```
#include "syscalls.h"

int read(int fd, char *buf, int n)

int getchar(void)
{
    char c;

    return (read(0, &c, 1) == 1) ? (unsigned char) c : EOF)
}
// Notice how read returns an int but we expect a char. Since EOF is -1, to prevent sign extension (system automatically promoting char to an int) we explicitly cast it to an unsigned char.
```
3. **Open, Creat, Close, Unlink** - Just as mentioned when we want to read and write to files, we first have to open them. The `open` syscall is similar to fopen but instead of returning a file pointer, it returns the file descriptor or -1 if an error occured. `creat` will create a new file or rewrite old ones and set permissions specified by the perms parameter argument. There are 9 bits of permissions usr,group,others `rwxrwxrwx`. Therefore it is convenient to use an octal number to represent this. This octal number is referred to as mode. There is about a mximum of 20 file descriptors that a process is allocated. Therefore you cannot have many opened files together. Using the `close` function will break the connection between the file descriptor and the opened file to be reused for another file. The syscall `unlink(char *name)` removes the file name from the file system and corresponds to the standard library function remove. It seems like in mac OSX, syscalls are hidden from the user C programs use the standard library that builds on syscalls to do similar functionality. [Implement `cat` with system calls instead of stdio libraries]
4. **Random Access - Lseek** - Usually when read or write to a file, it happens sequentially. However, it is possible to move around a file with lseek syscall. `long lseek(int fd, long offset, int origin)` allows us to treat a file like an array. The standard libary function fseek is similar to lseek except the first argument is a `FILE *`
5. **Example - An implementation of fopen and getc** - A `FILE *` points to the `FILE` struct which contains 
    - the pointer to a buffer. 
    - a count of the number of characters left in the buffer.
    - a pointer to the next position in the buffer
    - file descriptor
    - flags describing the read/write mode and error status
So we see that libraries are just an interface for easier programming for interacting with IO and implement syscalls. On the other hand syscalls are the interface to the IO themselves. In general, within libraries functions are defined with underscores _iobuf to minimize conflict with user program names. Both `getc` and `fopen` require the function `_filbuf` which creates and fills the buffer if no buffer has been allocated or `_flushbuf` if it is full and needs to be reinitialized



# Additional Notes

**Unix File descriptors vs Standard lib File pointers**


**Macro expansion vs Function calls**
- Macro expansion is generally prefered when you have a small routine instead of writing a function call. The reason for this is that extra resources are used when a function call is made such as copying values because of the pass by value property of arguments.
- On the other hand, macro expansion just copies the code during the preprossesing step so no values are copied over.
- However, most compilers today, inline their functions so it becomes analogous to macro expansion.

**What is a stream & buffer**
- A stream is just an interface representing a sequence of bytes/data. The use of this is so we have a uniform way of interacting with data regardless of source or destination.
- The name stream can be applied almost to any kind of data transfer whether it be by keyboard input or program output or file reading or writing. Data comes in quite intuitively as a sequence of data and a stream is just a way to describe this process.
- A buffer on the other hand, is a sequence of data stored in memory.
- A stream can be put in a buffer for easier handling.

**Function declaration vs definition**
- A declaration is merely telling the program what the function returns, and its argument types. A function is usually declared before being used in another function/program by a function protype. If a function protoype is not found. The functions return and argument types are implicitly declared by the first use in the program.
- A definition is the entire function code itself including it's argument variable names and it's body.
- A definition will reserve storage space for a function whereas a declaration decribes what the properties of a function are.

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