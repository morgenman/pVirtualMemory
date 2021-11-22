#ifndef VIRTUALMEMORYTYPES_H
#define VIRTUALMEMORYTYPES_H

/**
 * Type Declarations for clarity
 */
using PageNumber = unsigned int;
using FrameNumber = unsigned int;
using EventTime = unsigned int;
using Offset = unsigned int;
using VirtualAddress = unsigned int;
using PhysicalAddress = unsigned int;

/**
 * Null Values and Masking for bitwise operations
 */
const PageNumber noSuchPage = 0xFFFFF;
const FrameNumber noSuchFrame = 0xFFFFF;
const unsigned int pageMask = 0xFFFFF000;
const unsigned int frameMask = 0xFFFFF000;
const unsigned int offsetMask = 0x00000FFF;
const unsigned int offsetWidth = 12;  // Represented in bits

/**
 * Using bitwise operations, return page number.
 * Mask out the pageTable bits and shift right(depending on how you are viewing
 * endianess) by 12 bits, equivalent to 4 hex digits (as seen in the mask above)
 *
 * @param  {VirtualAddress} va : represented as an unint
 * @return {PageNumber}        : return index into pageTable as uint
 */
PageNumber getPage(VirtualAddress va);

/**
 * Using bitwise operations, return offset.
 * Mask out the offset bits. No need to shift or pad.
 *
 * @param  {VirtualAddress} va : represented as an unint
 * @return {PageNumber}        : return offset as uint
 */
Offset getOffset(VirtualAddress va);

#endif /* VIRTUALMEMORYTYPES_H */
