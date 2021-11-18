#ifndef PTE_H
#define PTE_H

#include <iostream>
#include "virtualMemoryTypes.h"
/**
 * A Page Table Entry
 *
 * The interface is defined in this header file.
 * The private data fields to support the interface are necessary.
 *
 * With no constructor the compiler generates a default (no-parameter)
 * constructor. You may write a default constructor to initialize
 * the data fields or use {} initialization to set the value of the
 * fields when they are declared.
 */
class PTE
{
public:
  /**
   * Get the FrameNumber from the PTE.
   *
   * @return the FrameNumber in the PTE if it is present;
   * noSuchFrame if the page is not present.
   */
  FrameNumber frame() const;

  /**
   * Set the FrameNumber from the PTE.
   *
   * Set the field regardless of whether or not it is present.
   *
   * @return the FrameNumber set in the PTE after it is set.
   */
  FrameNumber frame(FrameNumber newFrameNumber);

  /**
   * Is the PTE present in the RAM?
   *
   * @return true if the PTE is present in the given frame.
   */
  bool present() const;

  /**
   * Set the present "bit" in the PTE present in the RAM
   *
   * @param newPresent new value of present
   * @return value of present after it is set.
   */
  bool present(bool newPresent);

  /**
   * Has the page/PTE been referenced "recently"?
   *
   * @return true if PTE reference "bit" is set.
   */
  bool referenced() const;

  /**
   * Set the referenced "bit" in the PTE
   *
   * @param newReferenced new value of referenced bit
   * @return value of represented after it is set
   */
  bool referenced(bool newReferenced);

private:
  bool _present{};
  bool _referenced{};
  FrameNumber _frame{noSuchFrame};
};

/**
 * Output operator for one PTE
 *
 * Format:
 * |p|r|ffffffff|
 *
 * Where p is 0/1 representing the present bit
 * Where r is 0/1 representing the referenced bit
 * Where ffffffff is the associated frame number (if present)
 * or ffffffff (noSuchPage) otherwise.
 * Note: This format does NOT include an end of line.
 *
 * @param out target output stream to print on
 * @param pte the PTE to print
 * @return out for continued processing of the output stream
 */
std::ostream & operator<<(std::ostream & out, const PTE & pte);

#endif /* PTE_H */
