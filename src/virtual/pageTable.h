/**
 * PageTable class extends vector to implement a Page Table structure
 *
 * A Page Table 'caches' page => frame lookups, theoretically lowering the cost
 * for lookup. As such I have tried to keep the operations for these as simple
 * as possible
 *
 */
#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <iostream>
#include <vector>

#include "pte.h"
#include "virtualMemoryTypes.h"

/**
 * A vector of PTE representing the page table for a single process.
 *
 * Extends vector so that [] works for clients of the PageTable.
 */
class PageTable : public std::vector<PTE> {
 public:
  /**
   * Constructor takes the number of pages in the page table.
   */
  PageTable(const size_t n);

  /**
   * Clear the referenced bit in all PTE.
   */
  void clearReferenced();

  /**
   * Lookup the given page in the PageTable.
   *
   * @param p page number to translate to FrameNumber
   * @return the FrameNumber where the page is loaded (if it is present)
   * noSuchFrame otherwise
   */
  FrameNumber lookup(PageNumber p);

  /**
   * Find the lowest page number that is unreferenced.
   *
   * @return valid page number of an unreferenced, present page
   * if there is one; noSuchPage otherwise.
   */
  PageNumber findUnreferenced();

  /**
   * Find the page number associated with the give frame.
   *
   * @return page number of present page referring to given frame;
   * noSuchPage if there is no such page.
   */
  PageNumber findByFrame(FrameNumber frame);
};

/**
 * Output operator for PageTable
 * Output format is
 *
 *   # PTE
 *
 * Where # is the hex page number in a space-padded field width of 3.
 * @param out the output stream where the page table is to be printed
 * @param pageTable the page table to print
 * @return out; the output stream for continued processing
 */
std::ostream& operator<<(std::ostream& out, const PageTable& pageTable);
#endif /* PAGETABLE_H */
