
#include "frame.h"

/**
 * Get the page number associated with a non-free page.
 *
 * @return PageNumber associated with frame if frame is not free;
 * noSuchPage otherwise.
 */
PageNumber Frame::page() const {}

/**
 * Set the page number in the frame.
 *
 * @param newPage new value for the page number
 * @return PageNumber in frame after it is set
 */
PageNumber Frame::page(PageNumber newPage) {}

/**
 * Get the reference time in a non-free frame.
 *
 * @return EventTime that the frame was last referenced if it is non-free;
 * 0 otherwise.
 *
 */
EventTime Frame::timestamp() const {}

/**
 * Set the reference time in the frame.
 *
 * @param newReference new value for the time stamp
 * @return reference time after it is set
 */
EventTime Frame::timestamp(EventTime newReference) {}

/**
 * Is the frame currently free?
 *
 * @return true if free; false otherwise
 */
bool Frame::free() const {}

/**
 * Set the free bit in the frame.
 *
 * @param newFree the new value for the free bit
 * @return free bit after it is set
 */
bool free(bool newFree) {}