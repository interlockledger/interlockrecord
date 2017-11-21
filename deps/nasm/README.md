# NASM Dependency

**Netwide Assembler** or **NASM** is an assembler and disassembler for the
Intel/AMD x86 and x86-64 architectures.

In order to install it, goto  http://www.nasm.us/ and follow the instructions.

In order to be usable by other build scripts, make sure to add the directory
containing the executables to the PATH.

One suggestion to achieve this is to create a system variable called **NASM_HOME**
that points to the NASM files directory (the directory that contains the file
*nasm.exe*).

After that, append the **%NASM_HOME%** to the end of the definition of the
environment variable. This allows a fast update of the variable
