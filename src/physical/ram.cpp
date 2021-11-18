#include "ram.h"

RAM::RAM(const size_t n) {}

/**
 * Find the FrameNumber of a free frame, if one exists.
 *
 * @return lowest valid FrameNumber of a free Frame if one exists; noSuchFrame
 * if there are no free Frame in the RAM
 */
FrameNumber RAM::findFree() {}

/**
 * Find the FrameNumber of the Frame with the lowest referenced time stamp.
 *
 * @return FrameNumber of Frame where .referenced() method is the minimum
 * across RAM
 */
FrameNumber RAM::findOldest() {}

/**
 * Simulate loading a Frame with the contents of a given page.
 *
 * Actual content of Frame is a PageNumber (the one whose content it holds)
 * and a time stamp. This method simulates the loading of the content (and
 * the referenced time is updated elsewhere).
 *
 * Load the page to the lowest numbered free frame FrameNumber if there are any.
 * Select a FrameNumber to evict from RAM by
 * - the lowest .referenced() time of the Frame if useTimestamp is true,
 * otherwise
 * - the FrameNumber in the lowest PageNumber that has a zero .reference() bit,
 *   if one exists, and if none exists
 * - the FrameNumber of the lowest PageNumber that is .present() in RAM.
 *
 * @param p the PageNumber to load into RAM
 * @param pageTable the table of PTE; may be modified by loading
 * @param useTimestamp use Frame timestamps if true; use PTE referenced bits
 * if not.
 */
FrameNumber RAM::load(PageNumber p, PageTable& pageTable,
                      bool useTimestamp = true) {}