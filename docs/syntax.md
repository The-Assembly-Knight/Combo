# Combo Syntax

## Registers

**There are 4 types of registers ( A B X Y )**

Registers have different types, this types are not changeable and are necessary for Combo to be touring complete.

**A** -> Scratch register
**B** -> Scratch register
**X** -> Counter register
**Y** -> Output  register

**What is a scratch register?**

Scratch registers are meant to be used for arithmetic operations or on the other hand to store a value.

**What is a counter register?**

Counter registers are the main back bone of loops on Combo. Indeed, Combo's loops take the counter register as the amount of times the same piece of code most be repeated. Further explanation will be covered on the loops section.

**What is an output register?**

In simple words, an output register's main function is to store the value that will be printed when the print output combo is executed.


## Combos

First of all:

**What are combos?**

As its name suggests Combo is based on combos (this can be interpreted as actions or operations). This combos cover all the necessary operations for a programming language to be touring complete.

**Combos List:**

### Registers Combos

| Index  | Example     | Action      |
| :----- | :---------: | -------:    |
| 1		 | 	AB	       | Copying     |
| 2		 |	AXB	       | Moving      |
| 3		 |	AYB	       | Swaping     |
| 4      |  AAB        | Adding      |
| 5      |  ABB        | Subtracting |



1. **Copying**:

Copying a register to another register is as simple as to write the source and the destination registers.

**Example**:

    AB      this combo will copy register A to register B.
    BA      this combo will copy register B to register A.
    XY      this combo will copy register X to register Y.
    YX      this combo will copy register Y to register X.

2. **Moving**:

The difference between moving and copying is that, as its name suggests moving moves the contents of the source register to the destination register, which means the source register will be empty (0) after the combo is executed. This combo can be executed by doing copying with the X register before the destination register.

    Note: Take into account that moving a register to itself will be considered invalid syntax, and Combo will point it as a syntax error (or in terms of combo, an invalid combo).

**Example**:

    AXB     this combo will move the contents of register A to register B. Emptying register A in the process.
    BXA     this combo will move the contents of register B to register A. Emptying register B in the process.
    XXY     this combo will move the contents of register X to register Y. Emptying register X in the process.
    YXX     this combo will move the contents of register Y to register X. Emptying register Y in the process.

3. **Swaping**:

Swaping registers is as simple as to copying but using a Y between the source register and the destination register. In case you ask, swapping is an operation that moves the contents of the source register to the destination register and viceversa.

**Example**:

    AYB     this combo will swap the contents of register A and B, which means A will have the value of B and B will have the value of A.
    BYA     this combo will swap the contents of register B and A, which means B will have the value of A and A will have the value of B.
    XYY     this combo will swap the contents of register X and Y, which means X will have the value of Y and Y will have the value of X.
    YYX     this combo will swap the contents of register Y and X, which means Y will have the value of X and X will have the value of Y.

4. **Adding**:

Adding registers is simple, using register A between the source and destination register will grant the addition of the source register to the destination register, increasing the destination register value (as long as source register is > 0).

**Example**:

    AAB     this combo will add the contents of register A to register B, which means B will be equal to B+A. In addition, source register (A) will maintain its value.
    BAA     this combo will add the contents of register B to register A, which means A will be equal to A+B. In addition, source register (B) will maintain its value.
    XAY     this combo will add the contents of register X to register Y, which means X will be equal to X+Y. In addition, source register (X) will maintain its value.
    YAX     this combo will add the contents of register Y to register X, which means Y will be equal to Y+X. In addition, source register (Y) will maintain its value.

5. **Subtract**:

Subtract registers is simple, using register B between the source and destination register will grant the subtraction of the source register to the destination register, decreasing the destination register value (as long as source register is > 0).

**Example**:

    ABB     this combo will subtract the contents of register A to register B, which means B will be equal to B-A. In addition, source register (A) will maintain its value.
    BAA     this combo will subtract the contents of register B to register A, which means A will be equal to A-B. In addition, source register (B) will maintain its value.
    XAY     this combo will subtract the contents of register X to register Y, which means X will be equal to X-Y. In addition, source register (X) will maintain its value.
    YAX     this combo will subtract the contents of register Y to register X, which means Y will be equal to Y-X. In addition, source register (Y) will maintain its value.
