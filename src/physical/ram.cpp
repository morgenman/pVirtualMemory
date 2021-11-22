#include "ram.h"

RAM::RAM(const size_t n) { resize(n); }

FrameNumber RAM::findFree() {
  for (size_t i = 0; i < (*this).size(); i++)
    if ((*this)[i].free()) return i;
  return noSuchFrame;
}

FrameNumber RAM::findOldest() {
  FrameNumber oldest = 0;
  EventTime ts = (*this)[oldest].timestamp();
  for (size_t i = 0; i < (*this).size(); i++)
    if ((*this)[i].timestamp() < ts) {
      ts = (*this)[i].timestamp();
      oldest = i;
    }
  return oldest;
}

FrameNumber RAM::load(PageNumber p, PageTable& pageTable, bool useTimestamp) {
  // **** Part 1 *****
  FrameNumber free = findFree();
  if (useTimestamp) {
    if (free == noSuchFrame) free = findOldest();
  } else {
    PageNumber k = pageTable.findUnreferenced();
    if (k != noSuchPage) free = k;
    for (auto i : pageTable)
      if (i.present()) {
        free = i.frame();
        break;
      }
  }

  // **** Part 2 *****
  if (free == noSuchFrame)
    std::cout << std::endl
              << "ERROR: RAM::load() is trying to use noSuchFrame as an index"
              << std::endl;

  // **** Part 3 *****
  PageNumber p2 = pageTable.findByFrame(free);
  while (noSuchPage != p2) {
    pageTable[p2].frame(noSuchFrame);
    pageTable[p2].present(false);
    p2 = pageTable.findByFrame(free);
  }

  // **** Part 4 *****
  (*this)[free].free(false);
  (*this)[free].page(p);
  pageTable[p].frame(free);
  pageTable[p].present(true);
  return free;
}

std::ostream& operator<<(std::ostream& out, const RAM& ram) {
  for (int i = 0; i < (int)ram.size(); i++)
    out << "  " << i << " " << ram[i] << std::endl;
  return out;
}
