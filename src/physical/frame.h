#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include "virtualMemoryTypes.h"

/**
 * A Frame
 *
 * The interface is defined in this header file.
 * The private data fields to support the interface are necessary.
 *
 * With no constructor the compiler generates a default (no-parameter)
 * constructor. You may write a default constructor to initialize
 * the data fields or use {} initialization to set the value of the
 * fields when they are declared.
 */
class Frame {
public:
  /**
   * Get the page number associated with a non-free page.
   *
   * @return PageNumber associated with frame if frame is not free;
   * noSuchPage otherwise.
   */
  PageNumber page() const;

  /**
   * Set the page number in the frame.
   *
   * @param newPage new value for the page number
   * @return PageNumber in frame after it is set
   */
  PageNumber page(PageNumber newPage);

  /**
   * Get the reference time in a non-free frame.
   *
   * @return EventTime that the frame was last referenced if it is non-free;
   * 0 otherwise.
   *
   */
  EventTime timestamp() const;

  /**
   * Set the reference time in the frame.
   *
   * @param newReference new value for the time stamp
   * @return reference time after it is set
   */
  EventTime timestamp(EventTime newReference);

  /**
   * Is the frame currently free?
   *
   * @return true if free; false otherwise
   */
  bool free() const;

  /**
   * Set the free bit in the frame.
   *
   * @param newFree the new value for the free bit
   * @return free bit after it is set
   */
  bool free(bool newFree);

private:
  bool _free{true};
  PageNumber _page{noSuchPage};
  EventTime _reference{0};
};

/**
 * Output operator for one PTE
 *
 * Format:
 * if free then
 *   |       free|
 * else
 *   |fffff|ttttt|
 *
 * Where fffff is the loaded page number in hex
 * Where ttttt is the decimal time stamp in space padded 5 characters
 * Note: This format does NOT include an end of line.
 *
 * @param out target output stream to print on
 * @param frame the frame to be printed
 * @return out for continued processing of the output stream
 */
std::ostream & operator<<(std::ostream & out, const Frame & frame);

#endif /* FRAME_H */
