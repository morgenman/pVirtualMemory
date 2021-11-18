#ifndef VIRTUALMEMORYTYPES_H
#define VIRTUALMEMORYTYPES_H

using PageNumber = unsigned int;
const PageNumber noSuchPage = 0xFFFFF;
const unsigned int pageMask = 0xFFFFF000;
using FrameNumber = unsigned int;
const FrameNumber noSuchFrame = 0xFFFFF;
const unsigned int frameMask = 0xFFFFF000;
using EventTime = unsigned int;
using Offset = unsigned int;
const unsigned int offsetMask = 0x00000FFF;
const unsigned int offsetWidth = 12;
using VirtualAddress = unsigned int;
using PhysicalAddress = unsigned int;


PageNumber getPage(VirtualAddress va);
Offset getOffset(VirtualAddress va);
#endif /* VIRTUALMEMORYTYPES_H */
