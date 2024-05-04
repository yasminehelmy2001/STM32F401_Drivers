# Embedded C

## Data Types

![](/home/yasmin/Desktop/EmbeddedC/assets/DatatypesInC.jpg)

Void is used in

1. Function Argument

2. Function Return

3. Void Pointer

   

   

## Qualifiers

![](/home/yasmin/Desktop/EmbeddedC/assets/Qualifiers-in-C-Programming.jpg)





### Size qualifiers



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



### Sign Qualifiers

Lets look at the history of Sign Number Representation:

1. #### ***Sign Magnitude***

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

   

2) #### *1's Compliment*

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

   
   
3. #### *2's Compliment*

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



![](/home/yasmin/Desktop/EmbeddedC/assets/signed.png)

### Type Qualifiers

![](/home/yasmin/Desktop/EmbeddedC/assets/typequal.jpg)

