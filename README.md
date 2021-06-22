# The-C-Programming-Language-Exercises
A Repo containing my exercise solutions for "The C Programming Language" - by Brian Kernighan and Dennis Ritchie

You will find that this Repo is structured according the chapters in the book:
 - Chapter 1 (A Tutorial Introduction)
     - Compiling and printing your first "hello world" + string constants (hardcoded characters enclosed in quotes " ")
     - Variables and Arithmetic expressions (Temperature conversion table)
     - For loops (init; condition; expression)
     - Symbolic constants `#define` conducts replacement
     - Character IO `getchar()` and `putchar(c)` (file copying, character counting, line counting, word counting)
     - Arrays subscript operator []
     - Functions callable operator () & function prototypes
     - Arguments--Call by Value
     - Character arrays (Strings) and `'\0'` terminator value
 - Chapter 2 (Types, Operators, and Expressions)
    - Variable naming conventions (lowercase for variable names and upper case for symbolic constants)
    - Data types and sizes <em>(Read notes)</em>
    - Constants long constants have terminal `L` and unsigned constants have terminal `U`. enum constant
    - Declarations must be done before use! Declaration != Definition. Initializers must be static. An explicitly initialized variable is initialized everytime the function/block is entered. `external/static` is initializes as zero.
    - Arithmetic operators: associate left to right
    - Relational and Logical operators: Relational have less precedence than arithmetic operators. Expressions connected by logical operators evaluate left to right
    - Type conversions <em>(Read notes)</em>
    - Increment and Decrement Operators, postfix/prefix ++/--
    - Bitwise operators ~, &, |, ^, <<, >>, -`
 - Chapter 3 (Control Flow)
 - Chapter 4 (Functions and Program Structure)
 - Chapert 5 (Pointers and Arrays)
 - Chapter 6 (Structures)
    - Basic structure syntax
    - How to use structures in functions
    - Structure arrays `struct example[10]`
    - Pointers to structures and "`->`" syntax to access to members
    - Self referential structures (Tree structures)
    - Table lookup (Hashing and Linked list structures)
    - `typedef` keyword
    - `union` keyword
    - Bit-fields (Used for packing objects in a single word, E.g. Defining a set of masks alternatively fields can be used which are structs that have members which are explicitly defined unsigned/signed ints and with : \<bitsize\>)

<br>
<h1>Notes</h1>

<b>Data types:</b>
- A word is a fixed size of data that a computer processor is able to handle as a unit. It is machine dependent such as having 32/64 bit machines that indicate the word size that it is able to process at one go
- The main 4 data types are `char(1), int(2/4), float(4), double(8)`
- An int is either a 2/4 bytes long dependent on the machine.
- There are qualifiers such as short/long which tell compiler how to intepret the data sizes. Again a short and long is machine dependent. However the following rules apply. short <= int <= long
- There are qualifiers `signed` and `unsigned` which alters the range of values taken by the data type. E.g. a char is 8bits long which translates to 256 different representations. An unsigned char ranges from 0-255 whilst a signed char ranges from -128 - 127
- The way the processor treats signed datatypes is by using the (Twos complement machine) which finds the negative representation of a binary number as the inverted bits + 1. Therefore in a 3 bit system, 2 : 010 ~ inverted = 101 -> +1 = 110 : -2

<b>Differences between an expression & statement:</b>
- Expressions include variables, operators, callables, subscritors and anything that evaluates to some value.
- Statements on the other hand are generally a collection of expressions but may also include control flow, etc. Expressions are statements but the same is not true vice versa.

<b>Type Conversions</b>:
- As a general rule of thumb, narrower types get converted to wider types. Converting in the opposite is prone to information lost but are not illegal.
- When you implicitly/explicitly cast a type to a different one, it produces a new value but the original value and it's type is unchanged.