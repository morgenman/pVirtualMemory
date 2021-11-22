# pVirtualMemory
*Dylan Morgen  
CIS 310: Operating Systems*

## Introduction
Program reads a *virtual address trace* (mixed with some commands) and
translates it to a *physical* address trace. As written, the memory spaces, both
virtual and physical, are hardwired. Modifying the Frame and PTE classes allow it to be easily modified to implement more complex representations of virtual and physical memory.

## The command loop is provided in `main` (`vmSimulator.cpp`). It reads
standard input by line. The '#' character starts an EOLN style
comment, commands cannot span a line, and blank lines are ignored by
the processor.

A simulated clock, the event clock, is maintained and increments every
time an address is accessed.

## Commands
`READ XXXXXXXX`  
`WRITE XXXXXXXX`  
- These two commands contain the virtual address
  trace. The XXXXXXXX is a 32-bit virtual address expressed in
  hexadecimal. Each of these is processed by looking up the frame
  number using the page number and page table; if that fails (page is
  not loaded in a frame), then that page is loaded. When the page is
  accessed, the reference timestamp in the frame is updated to the
  current event clock value and the referenced bit in the page table
  is set.  

`PAGES`  
- The page table is dumped to standard output. The format for
  this is documented in the printing functions for a page table entry.

`FRAMES`  
- The content of the RAM (frames) is dumped to standard
  output. The format for this is documented in the printing function
  for a frame.

`TIME`  
- Use the frame timestamps to find the LRU "victim" frame on a
  page fault.

`REF`  
- Use the page referenced bit to find the LRU "victim" frame on
  a page fault.

`CLEAR`  
- Clear referenced bits for all pages.

## Building

Run the following in the root directory:
```bash
$ make
$ ./build/vmSimulator
```
To clean output executables first, run:
```bash
$ make clean
$ ./build/vmSimulator
```
> Note:
> This requires gcc-11 as the default compiler. To use an older one, change line 27 in `./Makefile` to read:
> ```makefile
> CFLAGS = -std=c++2a -O0 -Wall -Werror -g
> ```

## Testing

An instructor provided executable built for x86 Linux is located in `./tests/vmSimulator.benchmark`.  
Feel free to compare output for any inputs you can think of.  
To compare output with a sample input file run the following commands and see if the output matches:
```bash
$ ./build/vmSimulator < ./tests/trace00.txt
$ ./tests/vmSimulator.benchmark < ./tests/trace00.txt
```
