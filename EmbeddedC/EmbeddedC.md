# Embedded C

## Data Types

![](/media/yasmin/Yasmin/assets/DatatypesInC.jpg)

Void is used in

1. Function Argument

2. Function Return

3. Void Pointer

   

   

## Qualifiers

![](/media/yasmin/Yasmin/assets/Qualifiers-in-C-Programming.jpg)





### 1) Size qualifiers



`short` and `long`specifiers originally only applied to `int`, to give a range of integer sizes.

> short <= int >= long.
>

The size of char is always 1 byte, and the size of float is always 4 bytes, regardless of the platform or compiler. 

In the case of float or char , you can't assign short or long qualifiers to them.

Some machines support 80-bit extended double precision as well, and so `long double` was a natural way to express that type without using another keyword. You can't use `short double`.

> `Short `is only used with integers
>
> `Long` is only used with integers or double



**As per C Standard:**

1) char -> atleast 1 byte

2) int -> atleast 2 bytes

3) float -> atleast 4 bytes

4) double -> atleast 8 bytes

   

**For a 32-bit GCC compiler:**

| Data Type                  | Size (bytes) | Range                           | Format Specifier |
| -------------------------- | ------------ | ------------------------------- | ---------------- |
| **short int**              | 2            | -32,768 to 32,767               | %hd              |
| **unsigned short int**     | 2            | 0 to 65,535                     | %hu              |
| **unsigned int**           | 4            | 0 to 4,294,967,295              | %u               |
| **int**                    | 4            | -2,147,483,648 to 2,147,483,647 | %d               |
| **long int**               | 4            | -2,147,483,648 to 2,147,483,647 | %ld              |
| **unsigned long int**      | 4            | 0 to 4,294,967,295              | %lu              |
| **long long int**          | 8            | -(2^63) to (2^63)-1             | %lld             |
| **unsigned long long int** | 8            | 0 to 18,446,744,073,709,551,615 | %llu             |
| **signed char**            | 1            | -128 to 127                     | %c               |
| **unsigned char**          | 1            | 0 to 255                        | %c               |
| **float**                  | 4            | 1.2E-38 to 3.4E+38              | %f               |
| **double**                 | 8            | 1.7E-308 to 1.7E+308            | %lf              |
| **long double**            | 16           | 3.4E-4932 to 1.1E+4932          | %Lf              |



We use `typedef` for a standard data type size across all compilers:

​	Ex: 

```c
typedef unsigned char uint8;
```



### 2) Sign Qualifiers

Lets look at the history of Sign Number Representation:

#### 2.1) ***Sign Magnitude***

For every +ve number, its -ve number has its MSB=1.

> Example:
>
> ​	+1 -> 0000 0001
>
> ​	-1 -> 1000 0001



But this introduced some problems:

**1st problem:**

​	+0 -> 0000 0000

​	-0 -> 1000 0000

​	Now I have <u>2 representations for one number</u>! Adding them or subtracting them would lead to 	further problems!



**2nd problem:**

​	<u>Some unreliable mathematical operations</u>

​	+1 -> 0000 0001

​    +

​	-1 -> 1000 0001

_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

​	  1000 0010  -> (-2)



--------------------------------------------------



#### 2.2)*1's Compliment*

For every +ve number, its -ve is its compliement. (~)

> Example:
>
> ​	+1: 0000 0001
>
> ​	-1: 1111 1110

Lets see if this solved the problems I was facing:



**1st problem:**

​	+0 -> 0000 0000

​	-0 -> 1111 1111

<span style="color:red">Not solved</span>



**2nd problem:**



​	+1 -> 0000 0001

​    +

​	-1 -> 1111 1110

_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

​	 1111 1111 -> (-0)

<span style="color:green">Solved</span>



#### 2.3) *2's Compliment*

For every +ve number, its -ve is (1's compliment+1)

> Example:
>
> ​	+1: 0000 0001
>
> ​	-1: 1111 1111

Lets see if this solved the problems I was facing:



**1st problem:**

​	+0 -> 0000 0000

​	-0 -> 0000 0000

<span style="color:green">Solved</span>



**2nd problem:**



​	+1 -> 0000 0001

​    +

​	-1 -> 1111 1111

_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _

​	 0000 0000 -> (0)

<span style="color:green">Solved</span>



**So -ve numbers are represented by 2's compliment**

----------------------------------------------------

Note 1: Signed characters representation is from -128 to 127

Note 2: Negative numbers begin with '1',Positive numbers begin with '0'.

Note 3: We can’t we use `unsigned` and `signed` with a floating/double.

Note 4: short signed int = signed short int

Note 5: don't use 2 modifiers of the same type



![](/media/yasmin/Yasmin/assets/signed.png)

### 3) Type Qualifiers

![](/media/yasmin/Yasmin/assets/typequal.jpg)

When a variable is declared as `volatile`, it informs the  compiler that the variable can be changed unexpectedly by sources  outside the current code flow, such as ISRs or hardware registers. 



## Escape Sequences 

![](/home/yasmin/Desktop/EmbeddedC/assets/Escape-Sequence-is-C.png)



## Storage Classes

`Storage Duration`: The variable you defined will stay in memory for how long? and in which part of the memory?

`Automatic Storage Duration`: Temporary Storage Duration.

`Static Storage Duration`: Permanent Storage Duration.

![](/home/yasmin/Desktop/EmbeddedC/assets/Storage-Classes-in-C-with-Examples.png)

`Internal Linkage`: Static global variables: can't be externed. Trying to extern it will give <span style="color:red">Linker Error: Undefined reference to ...</span>

`External Linkage`: Global variables: can be externed.

![](/home/yasmin/Desktop/EmbeddedC/assets/C++2.jpg)

Static + Local variables change storage duration from `automatic` to `static`.



## Memory Layout

![](/home/yasmin/Desktop/EmbeddedC/assets/section_map.drawio.svg)

#### *1) Local variables*

```c
int main ()
{
    uint8_t x1=10;						-> stack
    uint8_t x2;							-> stack
        
    const uint8_t x3;					//compilation error
    const uint8_t x4=11;				-> stack
        
    static uint32_t x5=9				-> .data
        
    static uint32_t x6;				-> .bss
    static uint32_t x7=0;				-> .bss
        
    static const uint32_t x8=90;		-> .rodata		
    static const uint32_t x9=0;		-> .rodata		
    
}
```

#### *2) Global variables*

```c
static uint32_t var=9				-> .data
static uint32_t var2;				-> .bss
static const uint32_t var3=90;		-> .rodata
const uint8_t var4;					//compilation error
const uint32_t var5=90;				-> .rodata
```

To view where variables are saved in which sections, use this compiler flag:

`-Wl,-Map=output.map`

> The `-Wl` flag in GCC is used to pass options directly to the linker. When you use `-Wl` followed by a comma-separated list of options, GCC passes those options to the linker without interpreting them itself.
>
> The `-Map` option instructs the linker to generate a map file (`output.map` in this case) containing information about the program's memory layout, sections, symbols, and their addresses. 



## Compiler Flags

Create position independent code( -fPIC)

```
gcc -c -fPIC file.c
```

Convert warnings to errors (-Werror)

```
gcc -Werror file.c
```

Add debugging information

```
gcc -g file.c -o file
```

> With debugging information included, tools like GDB (GNU Debugger) can map machine instructions back to the corresponding lines in the original source code. This makes it much easier to debug issues in your program while it's running.

Generate Makefile

```
gcc -MM file.c
```

 Specify architecture

```
gcc -m32 file.c    
```

Get pretty assembly output

```
gcc file.c -S -masm=intel -fverbose-asm -o file.S
```

Preprocessed Code

```
gcc -E file.c
```

Assembly Code

```
gcc -S file.i -o file.S
```

Object file

```
gcc -c file.S -o file.o
```

Linking

```
gcc file.o -o file
```

Linking with shared libraries (-l)

```
gcc file.c -o file -lCPPFILE
```

 Produce only compiled code

```
gcc -c file.c    
```



## Endianess

![](/home/yasmin/Desktop/EmbeddedC/assets/1704128198851.gif)

```c
uint32_t var=0x12345678;
uint32_t*ptr=&var;
uint16_t*ptr16=(uint16_t)ptr;
uint8_t*ptr8=(uint8_t)ptr;

Little Endian:
ptr->	78	
		56
		34
		12
    
*ptr= 0x12345678
*ptr16=0x5678 
*ptr8= 0x78
   
Pointer goes to first address and reads from it
Compiler organizes according to endianness
```

## Operators

### 1) Operators in C

![](/home/yasmin/Desktop/EmbeddedC/assets/Operators-In-C.png)

### 2) Operator Precedence and Associativity

![](/home/yasmin/Desktop/EmbeddedC/assets/prec.png)

## Build Process

## Type Conversion - Typecasting

## Pointers

## String

## Data in Memory

## Dynamic Memory Allocation

## Header Guard

## Preprocessor Directives

## Optimization

## Floating Data Type

## Make File

## GDB

## Cache Memory

