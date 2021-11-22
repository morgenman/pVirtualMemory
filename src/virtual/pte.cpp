#include "pte.h"

#include <iomanip>

PTE::PTE() {
  _present = false;
  _referenced = false;
  _frame = noSuchFrame;
}

FrameNumber PTE::frame() const { return _frame; }

FrameNumber PTE::frame(FrameNumber newFrameNumber) {
  // Uncomment for optional implementation where present bit is managed by PTE
  // set function
  // if (newFrameNumber == noSuchFrame) _present = false;
  return _frame = newFrameNumber;
}

bool PTE::present() const { return _present; }

bool PTE::present(bool newPresent) { return _present = newPresent; }

bool PTE::referenced() const { return _referenced; }

bool PTE::referenced(bool newReferenced) { return _referenced = newReferenced; }

std::ostream& operator<<(std::ostream& out, const PTE& pte) {
  out << " |" << pte.present() << "|" << pte.referenced() << "|" << std::hex
      << std::setw(5) << std::setfill('0') << pte.frame() << "|";
  return out;
}
