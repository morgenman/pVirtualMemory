
#include "frame.h"

#include <iomanip>

Frame::Frame() {}
Frame::Frame(bool free, PageNumber pn) {
  _free = free;
  _page = pn;
}

/**
 * Get the page number associated with a non-free page.
 *
 * @return PageNumber associated with frame if frame is not free;
 * noSuchPage otherwise.
 */
PageNumber Frame::page() const {
  if (_free) return noSuchPage;
  return _page;
}

/**
 * Set the page number in the frame.
 *
 * @param newPage new value for the page number
 * @return PageNumber in frame after it is set
 */
PageNumber Frame::page(PageNumber newPage) { return _page = newPage; }

/**
 * Get the reference time in a non-free frame.
 *
 * @return EventTime that the frame was last referenced if it is non-free;
 * 0 otherwise.
 *
 */
EventTime Frame::timestamp() const {
  if (_free) return 0;
  return _reference;
}

/**
 * Set the reference time in the frame.
 *
 * @param newReference new value for the time stamp
 * @return reference time after it is set
 */
EventTime Frame::timestamp(EventTime newReference) {
  return _reference = newReference;
}

/**
 * Is the frame currently free?
 *
 * @return true if free; false otherwise
 */
bool Frame::free() const { return _free; }

/**
 * Set the free bit in the frame.
 *
 * @param newFree the new value for the free bit
 * @return free bit after it is set
 */
bool Frame::free(bool newFree) { return _free = newFree; }

std::ostream& operator<<(std::ostream& out, const Frame& frame) {
  if (frame.free())
    out << " |       "
        << "free|";
  else
    out << " |" << std::hex << std::setw(5) << std::setfill('0') << frame.page()
        << "|" << std::setw(5) << std::setfill(' ') << std::dec
        << frame.timestamp() << "|";
  return out;
}
