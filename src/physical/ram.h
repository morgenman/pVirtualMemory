#ifndef RAM_H
#define RAM_H
#include <algorithm>
#include <vector>

#include "frame.h"
#include "pageTable.h"
#include "virtualMemoryTypes.h"

/**
 * RAM is vector of Frame objects indexed by their FrameNumber.
 *
 * It takes a size parameter on construction and is expected to remain fixed.
 *
 * All Frame are initially free (their .free() method returns true). Once
 * content has been put into a Frame, it will never again be free.
 */
class RAM : public std::vector<Frame> {
 private:
 public:
  /**
   * Constructor: builds a new RAM with n free Frame in it.
   *
   * @param n number of Frame in the RAM
   */
  RAM(const size_t n);

  /**
   * Find the FrameNumber of a free frame, if one exists.
   *
   * @return lowest valid FrameNumber of a free Frame if one exists; noSuchFrame
   * if there are no free Frame in the RAM
   */
  FrameNumber findFree();

  /**
   * Find the FrameNumber of the Frame with the lowest referenced time stamp.
   *
   * @return FrameNumber of Frame where .referenced() method is the minimum
   * across RAM
   */
  FrameNumber findOldest();

  /**
   * Simulate loading a Frame with the contents of a given page.
   *
   * Actual content of Frame is a PageNumber (the one whose content it holds)
   * and a time stamp. This method simulates the loading of the content (and
   * the referenced time is updated elsewhere).
   *
   * Load the page to the lowest numbered free frame FrameNumber if there are
   * any. Select a FrameNumber to evict from RAM by
   * - the lowest .referenced() time of the Frame if useTimestamp is true,
   * otherwise
   * - the FrameNumber in the lowest PageNumber that has a zero .reference()
   * bit, if one exists, and if none exists
   * - the FrameNumber of the lowest PageNumber that is .present() in RAM.
   *
   * @param p the PageNumber to load into RAM
   * @param pageTable the table of PTE; may be modified by loading
   * @param useTimestamp use Frame timestamps if true; use PTE referenced bits
   * if not.
   */
  FrameNumber load(PageNumber p, PageTable& pageTable,
                   bool useTimestamp = true);
};

/**
 * Output operator for RAM
 * Output format is
 *
 *   # Frame
 *
 * Where # is the hex page number in a space-padded field width of 3 and
 * Frame is the output
 * @param out the output stream where the RAM is to be printed
 * @param ram the memory to print
 * @return out; the output stream for continued processing
 */
std::ostream& operator<<(std::ostream& out, const RAM& ram);

#endif /* RAM_H */
