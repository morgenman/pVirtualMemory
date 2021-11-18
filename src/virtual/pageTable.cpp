#include "pageTable.h"

/**
 * Constructor takes the number of pages in the page table.
 */
PageTable::PageTable(const size_t n);

/**
 * Clear the referenced bit in all PTE.
 */
void PageTable::clearReferenced();

/**
 * Lookup the given page in the PageTable.
 *
 * @param p page number to translate to FrameNumber
 * @return the FrameNumber where the page is loaded (if it is present)
 * noSuchFrame otherwise
 */
FrameNumber PageTable::lookup(PageNumber p);

/**
 * Find the lowest page number that is unreferenced.
 *
 * @return valid page number of an unreferenced, present page
 * if there is one; noSuchPage otherwise.
 */
PageNumber PageTable::findUnreferenced();

/**
 * Find the page number associated with the give frame.
 *
 * @return page number of present page referring to given frame;
 * noSuchPage if there is no such page.
 */
PageNumber PageTable::findByFrame(FrameNumber frame);
