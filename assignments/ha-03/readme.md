# Homework Assignment 3 (due Oct 28th 11:59pm)

In this assignment, we will explore compiling, linking, and loading **RISC-V binary files**. 
The assignment is worth a total of 100 points.  If you have any questions or need 
assistance, please don't hesitate to reach out to us during office hours or post 
your questions on the `Ed Discussion` forum.

## Preliminaries

You will work remotely using the `RISC-V` toolchain.  The required software is
set up and available on the `homework` server. To login, simply open a 
terminal and type the following command:

```bash
$ ssh <username@machine>
```

You will be prompted for your password.  Once you have logged in, you can
run the following command to access the `RISC-V` toolchain:

```bash
$ export PATH=$PATH:/usr/local/riscv/bin
```

The list of tools that you will/might use in this assignment are:

- `riscv32-unknown-elf-gcc` -- The RISC-V cross-compiler
- `riscv32-unknown-elf-run` -- The RISC-V simulator
- `riscv32-unknown-elf-objdump` -- The RISC-V object file utility
- `riscv32-unknown-elf-readelf` -- The RISC-V ELF file utility
- `riscv32-unknown-elf-nm` -- The RISC-V symbol table utility

## Task 1

Transfer the starter code for this assignment to the `homework` server.
Useful tools for transferring files are `scp` or `sftp`.  You may also
use the copy/paste method from your computer to the terminal window
connected via `ssh` to the server.  There are a few text editors that
you can use on the server, such as `vim`, `pico`, or `nano`. Some other
useful commands for file manipulation are `ls`, `cd`, `pwd`, `mv`, 
`cp`, and `rm`.

## Task 2

The starter code includes three files: `main.c`, `sum.c`, and `sum.h`.
Your first task is to read the code to understand its purpose and 
paying particular attention to: global variables, local variables, 
functions.

You can compile and link all source files and generate a binary
 with the command below:

```bash
$ riscv32-unknown-elf-gcc main.c sum.c -o prog
```

Given that we are using a RISC-V cross-compiler, the output binary
file will encode instructions using the RISC-V instruction set (RV32i).
You won't be able to run the binary file directly (the hardware is 
an x86 machine), but you can use the `riscv32-unknown-elf-run` tool 
to simulate the execution of the binary file.  The command below
runs the binary file:

```bash
$ riscv32-unknown-elf-run prog
```

## Task 3

Now that you have compiled and run the binary file, your next task is to
use the `riscv32-unknown-elf-gcc` compiler to generate the assembly code
and the object file.  The commands below generate the assembly code for 
`sum.c` using no optimizations and optimization level 3 respectively: 

```bash
$ riscv32-unknown-elf-gcc -O0 -S sum.c -o sum-no-opt.s
$ riscv32-unknown-elf-gcc -O3 -S sum.c -o sum-opt.s
```

Your task is to compare the assembly code generated with no optimizations
and optimization level 3 (focus on the instructions and labels and ignore 
the other directives that start with a `.`).  You will try to trace the 
differences in the assembly code and understand the impact of the 
optimizations on the original code. 

>[!Note]
> What are the changes from the unoptimized code to the optimized code.
> Submit your answer to this question via Gradescope.

## Task 4

Your next task is to generate the object files for the `main.c` and `sum.c`.
The following command will generate the object files for both source files:

```bash
$ riscv32-unknown-elf-gcc -O0 -c main.c sum.c
```
Now lets inspect the object files.  Use the following command to show the
symbol table of `sum.c`:

```bash
$ riscv32-unknown-elf-readelf -s sum.o
``` 

You will see a list of symbols, including the function `sum_array` and the global
variable `sum_counter`.  The symbol table also includes the size of the symbol,
the type of symbol, and the section where each symbol is located.

>[!Note]
> Submit your answers to the following question via Gradescope: 
>
> ### 4.1
> What is the size of the `sum_array` function in the object file? Can you elaborate
> on what exactly that value represents?
>
> ### 4.2
> What is the size of the `sum_counter` global variable in the object file? As you 
> can see this variable is located in the `.sbss` section.  What is the role of
> this section?
>
> ### 4.3
> You will notice that there are two labels (part of the loop) within the function
> `sum_array`.  They both have a hexadecimal number in the second column.  What is 
> the meaning of both numbers?

## Task 5

Now you will inspect the final executable file `prog` using the following command:

```bash
$ riscv32-unknown-elf-readelf -s prog
```

Search for the symbols `sum_array` and `sum_counter` in the symbol table of the
executable file.  You may want to use the `grep` command to filter the output.

>[!Note]
> What are the differences between the symbols in the object file and the 
> final executable file?  Explain the differences.  Submit your answer 
> via Gradescope.

## Task 6

You will use the command below to disassemble the executable file `prog`:

```bash
$ riscv32-unknown-elf-objdump -d prog
```

It may be helpful to redirect the output to a file for further analysis.
You can do this by appending `> prog-disassembly.txt` to the command above.
Look into the output of the disassembly and find the start of the function 
`sum_array`.  

>[!Note]
> Submit your answers to the following question via Gradescope: 
>
> ### 6.1
> What is the address of the first instruction of the `sum_array` function?
> 
> ### 6.2
> Are the instruction encodings you see using big-endian or little-endian?
> How can you tell?

## Task 7

Using the `riscv32-unknown-elf-readelf` tool with the option `-S` will 
display the section headers of the given file.  Use such command to
answer the following questions:

>[!Note]
> 
> ### 7.1
> Considering the program `sum.o`, what is the size of the `.text` section
> (in bytes)?  How many instructions are in the `.text` section?
> 
> ### 7.2
> Considering the program `main.o`, what is the size of the `.text` section
> (in bytes)?  How many instructions are in the `.text` section?
> 
> ### 7.3
> Considering the object `prog`, what is the size of the `.text` section
> (in bytes)?  How many instructions are in the `.text` section?
> 
> ### 7.4
> Why the big difference in the number of instructions between `prog` and
> the sum of the instructions in `sum.o` and `main.o`?

## Task 8
Run the command `history 100 > history.txt` to save the history of the commands
you have used in this assignment.

>[!Note]
> Submit the contents of the file `history.txt` via Gradescope.

> [!CAUTION]
> Remember, academic integrity is of utmost importance.  Any attempts at
> cheating or plagiarism will result in a forfeiture of credit.  Potential
> further actions include failing the class or referring the case for
> disciplinary measures.
