#qemu
First will start looking into our microprocessor stm32f407 both on live hardware and a simulator named QEmu.
 Then we will continue with stm32f407 hardware and protheus simulation.
 For installation of qemu and stm32f407-disco board see: https://www.youtube.com/watch?v=CdH-cad8DSw&list=PLpCEOpUHGlQYcmeNmdJSVX17VdQHkRO-o&index=8. Despite the tutorial is on linux it does not matter since all the installation is done via npm. (hence install nmp on your os)
## How numbers are counted?

int main() {
    int counter = 0;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;

    return 0;
}

Views usefull are register, memory and dissassembly as well as variables views ( I use 4 row 1 column).
see the instructions in memory: most of the Arm cortex m instructions occupy two bytes (see thumb and thumb 2 instruction set.)
Step into the code and  check PC (program counter) and the value in it at each iteration.
In which register is the variable stored?
What is a register ?: Memory which the microprocessor can read, clear and set.
İn arm cortex m4 thera are sixteen registers (pc is R15)
Machine instructions can manupilate registers easily and fast typically in one cycle.
SEt count to 0x7fffffff and increase 1;

Oxffffffff=-1;
0x80000000=-2^31
0x7fffffff=2 ^31 -1
0x00000001=1
change variable to unsigned. and set to 0x7fffffff
## Flow of control

int main() {
    int counter = 0;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;
    ++counter;

    return 0;
}
Look at the instructtion adress and the value of pc Counter
! How does the pc increment
Change the code
int counter = 0;
	while (counter <21)
	{
		++counter;
	}

Flow of loop   first check the counter then increase counter. İs it the same in disassembly?
when in compare pay attention to cspr :https://developer.arm.com/documentation/ddi0406/b/System-Level-Architecture/The-System-Level-Programmers--Model/ARM-processor-modes-and-core-registers/Program-Status-Registers--PSRs-

The CMP instruction has a very interesting side effect of modifying the
APSR register, which stands for Application Program Status Register.
Specifically, the CMP instruction sets the N-bit (negative) in the APSR,
because the comparison is performed as a difference R0-21, which turns
out negative.

The BLT instruction is a variant of the Branch instruction you already
saw, but this one is conditional. Specifically, the the BLT instruction
modifies the PC only when the N-bit in the APSR is set. Otherwise the
BLT instruction simply falls through to the next instruction.

At this point a good question is this: "How does the Branch instruction
know where to jump?"

Well, it turns out that this information is encoded in the instruction.
f9dd is the opcode, indeed it is ddf9 ! look at a.6.7.12 at 
http://web.eecs.umich.edu/~prabal/teaching/eecs373-f10/readings/ARMv7-M_ARM.pdf
the real number is ddf9 by the way



branching causes stalls in the fetch decode execute pipeline
##Variables and pointers
int counter = 0;
int main() {
    
    while (counter < 21) {
     ++counter;
    }

    
    return 0;
}
Compare disassembly

int counter = 0;

int main() {
    int *p_int;
    p_int = &counter;
    while (*p_int < 21) {
        ++(*p_int);
    }

   

    return 0;
}
int counter = 0;

int main() {
    int *p_int;
    p_int = &counter;
    while (*p_int < 21) {
        ++(*p_int);
    }

    p_int = (int *)0x20000002U;
    *p_int = 0xDEADBEEF;

    return 0;
}
watch for disallignment and follow the value in registers
##How do mcu interact with pins
int main() { int counter = 0;


	*((unsigned volatile int *) 0x40023830)=0x08u;
	*((unsigned volatile int *) 0x40020c00)=0x10000000u;

	*((unsigned volatile int *) 0x40020c14)=0x4000u ;
	 ;//otyper
	*((unsigned volatile int *) 0x40020c14)=0x0000u ;
	*((unsigned volatile int *) 0x40020c14)=0x4000u;


return 0;
}


##Midterm Question1 (for both simulation and project track): 10 points

you have for leds on your board. You are to pick two leds depending on your name and surname. You should find the ascii values of the chars in your name add them and take the mod of the resultant number. For instance ascii values of the string "gokhan"is103 111 107 104 97 110 . İf you add 103 + 111 + 107 +104 +97 +110 =632. 632 mod 4 is 0.  The ascii sum of the string is 531 and 531 mod 4 is 3.
The mapping of the led values to the resultant value is: 0 red, 1 blue, 2 orange and 3 is green.
So the leds that should be chosen  are red and green.
You are to write , implement and test the following functions:
a) init-leds (): find the necessary clock for the bus and and enable it.
b)turn_name_on(): light the led related to your name.
c)turn_surname_on():light the led related to your surname.
d) turn_name_of();turn of  the led related to your name.
e)turn_surname_of();turn of  the led related to your surname.

Note: 1) YOU ARE only allowed to use register adresses for turning the leds on and of. (NO hal  or cmsis library for turning the leds on)
2) You are to blink your name led as much as the letters in your name and to blink the surname letters as much as the number of chars in your surname. You are to debug the application using qemu emulator. 
3) You should create a repository named midtermquestion2. İn the repo you should have two directories: 
one is your projetc folder. The other directory should be named source and only include the source code you have written.
4) You should also either upload or supply a link to a short video  showing the result of your application.
%) You should upload your repository link to yulearn.

Any missing part will result in 0 grades for this question.
Your code might be randomly selected for code comparison using the  Measure Of Software Similarity (MOSS) and is subject to resemblance penalty.
## define and bit mask volatile,
Header in stm32f407xx
/*
    unsigned int a = 0x5A5A5A5A;
    unsigned int b = 0xDEADBEEF;
    unsigned int c;

    c = a | b;   // OR
    c = a & b;   // AND
    c = a ^ b;   // XOR
    c = ~b;      // NOT
    c = a << 1;  // right-shift
    c = a << 2;
    c = b >> 1;  // left-shift
    c = b >> 3;

    int x = 1024;
    int y = -1024;
    int z;

    z = x >> 3;
    z = y >> 3;
*/ now set masks for the registers.
 GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);

    /* start with turning all LEDs off */
    GPIO_PORTF_DATA_R &= ~(LED_RED | LED_BLUE | LED_GREEN);

    GPIO_PORTF_DATA_R |= LED_BLUE;

##Midterm Question2 (10 points) (for both simulation and project track): İmplement the schematic of the stmf407discovery board's leds pheripheral in proteus and run your answer to 1'st question on proteus.
#Stack overflow

void delay();
void delay() {
    int counter;
  
    counter = 0;
    while (counter < 50000) {  // delay loop
        ++counter;
    }
}
int main() { int counter = 0;


	*((unsigned volatile int *) 0x40023830)=0x08u;
	*((unsigned volatile int *) 0x40020c00)=0x10000000u;

	*((unsigned volatile int *) 0x40020c14)=0x4000u ;
	 ;//otyper
	 while(1)
	 {
	*((unsigned volatile int *) 0x40020c14)=0x0000u ;
	delay();
	*((unsigned volatile int *) 0x40020c14)=0x4000u;

	 }
return 0;
}

How does your processor calls your function ->  bl instruction, branch instructions change the pc register.
Bl also writes the adress of next instruction tp link register.
0x0800021a: ff f7 d5 ff   bl      0x80001c8 <delay>
branch to adress  0x80001c8 write the next adress to LR. (which is 0x0800021e)
lr	0x800021f (Hex)	? why	Thumb2 instruction set pecularity.
What does the function do?
0x080001c8: 80 b4         push    {r7}  //store r7 in the stack
0x080001ca: 83 b0         sub     sp, #12   // arange the stack register. Subtract 12 from the sp.
0x080001cc: 00 af         add     r7, sp, #0
C stack: a data structure representing a region of rem that grows as you add items and shrinks when you remove the rem.
SR: register that holds the last adress of the stack. In arm stack grows towards the lower memory adress. so subtracting twelve grows the stack by 12 units.
at the function exit reverse the changes to stack.
function is finished with bx : branch and exchange  bx lr, set pc to lr (or -1?).
All the values in the pc must be even (lsb is 0)
Last bit in LR : instruction set exchange bit
bit is 1 => Thumb instrucrtion set
bit is 1 => Arm instrucrtion set
Cortex M can not to switch to Arm instruction set.

Push saves the specified registers on the stack.-> to know where to turn to ofter bl or bx and automatically grows the stack
### Function Arguments

void delay(int);
void delay(int item) {
    int counter;
  
    counter = 0;
    while (counter < item) {  // delay loop
        ++counter;
    }
}
int main() { int counter = 0;


	*((unsigned volatile int *) 0x40023830)=0x08u;
	*((unsigned volatile int *) 0x40020c00)=0x10000000u;

	*((unsigned volatile int *) 0x40020c14)=0x4000u ;
	 ;//otyper
	 while(1)
	 {
	*((unsigned volatile int *) 0x40020c14)=0x0000u ;
	delay(50000);
	*((unsigned volatile int *) 0x40020c14)=0x4000u;

	 }
return 0;
}
0x08000216: 4c f2 50 30   movw    r0, #50000      ; 0xc350 
is argument pushed to stack ?
unsigned fact(unsigned n) {
// 0! = 1
// n! = n*(n-1)!  for n > 0

    if (n == 0U) {
        return 1U;
    }
    else {
        return n * fact(n - 1U);
    }
}

Watch how the stack changes and order of returns.
there must be some agreement between the caller of a function and
the function being called:  both sides must have an
understanding that the return address will be provided to the function
in the LR register. Also, both parties must agree that the first
argument will be passed in R0 and that the return value will be returned
in R0 as well.

Of course there are many more such little agreements that all form a
whole formal contract called the ARM Appication Procedure Call Standard
(AAPCS).
##ARM Appication Procedure Call Standard
the registers R0-R3 and R12 are used for passing arguments and
returning values, and can be clobbered by a function. On the other hand,
the function must preserve the 8 registers R4-R11. This doesn't mean
that a function cannot use R4-R11, but if it does, the function code
must save them on the stack and restore before returning.
unsigned fact(unsigned n) {
// 0! = 1
// n! = n*(n-1)!  for n > 0
unsigned foo[100];
foo[n]=n;
    if (n == 0U) {
        return 1U;
    }
    else {
        return foo[n] * fact(n - 1U);
    }
}
###Static keyword
keep the variable out of the stack hence always reachable.
##stdint
So far in this course, you have been only using the C built-in integer
types, such as 'int' or 'unsigned'. The problem with these built-in
types is that the C Standard does not actually prescribe their size. For
example, 'int' or 'unsigned' can be 32-bit wide on a 32-bit machine,
such as ARM, but they can be only 16-bit wide on a 16-bit or 8-bit
machines, such as MSP430 or AVR.

Beyond 'int' and 'unsigned', the C language offers also 'short' and
'unsigned short', 'long' and 'unsigned long', as well as 'char' and
'unsigned char' built-in data types. But, here again the C standard
prescribes only that the size of 'short' must not be bigger than int and
int must be not bigger than long. The plain 'char' data type is
typically one byte, but it can be either signed or unsigned, depending
on the compiler options.

All these ambiguities are actually intentional in the original C
standard to give the compiler vendors more flexibility, but in embedded
work it is often imperative to know exactly the size, signedness, and
dynamic range of your variables, so that your code runs the same way,
regardless of the target processor.
C99 ISO Standard, which provides the standard header file 'stdint.h'. For an
embedded programmer, the 'stdint.h' header file is one of the most
valuable features of the C99 Standard.


As you can see in stdint.h, the file uses typedefs to define the following
fixed-width integer types:

int8_t:   for signed 8-bit integer
uint8_t:  for unsigned 8-bit integer

int16_t:  for signed 16-bit integer
uint16_t: for unsigned 16-bit integer

and finally

int32_t:  for signed 32-bit integer
uint32_t: for unsigned 32-bit integer

The file defines more types, but these six are the most important.












