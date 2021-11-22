#include "virtualMemoryTypes.h"

PageNumber getPage(VirtualAddress va) {
  return ((va & pageMask) >> offsetWidth);
}

Offset getOffset(VirtualAddress va) { return (va & offsetMask); }