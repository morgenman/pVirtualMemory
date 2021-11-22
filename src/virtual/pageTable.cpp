#include "pageTable.h"

PageTable::PageTable(const size_t n) { resize(n); }

void PageTable::clearReferenced() {
  for (auto i : (*this)) i.referenced(false);
}

FrameNumber PageTable::lookup(PageNumber p) {
  if ((*this).at(p).present()) return (*this)[p].frame();
  return noSuchFrame;
}

PageNumber PageTable::findUnreferenced() {
  for (int i = 0; i < (int)(*this).size(); i++)
    if (!(*this).at(i).referenced()) return i;
  return noSuchFrame;
}

PageNumber PageTable::findByFrame(FrameNumber frame) {
  for (int i = 0; i < (int)(*this).size(); i++)
    if ((*this)[i].present() && (*this)[i].frame() == frame) return i;
  return noSuchPage;
}

std::ostream& operator<<(std::ostream& out, const PageTable& pageTable) {
  for (int i = 0; i < (int)pageTable.size(); i++) {
    out << "  " << std::hex << i << " " << pageTable[i] << "\n";
  }
  return out;
}