#include "pte.h"

/**
 * Get the FrameNumber from the PTE.
 *
 * @return the FrameNumber in the PTE if it is present;
 * noSuchFrame if the page is not present.
 */
FrameNumber PTE::frame() const;

/**
 * Set the FrameNumber from the PTE.
 *
 * Set the field regardless of whether or not it is present.
 *
 * @return the FrameNumber set in the PTE after it is set.
 */
FrameNumber PTE::frame(FrameNumber newFrameNumber);

/**
 * Is the PTE present in the RAM?
 *
 * @return true if the PTE is present in the given frame.
 */
bool PTE::present() const;

/**
 * Set the present "bit" in the PTE present in the RAM
 *
 * @param newPresent new value of present
 * @return value of present after it is set.
 */
bool PTE::present(bool newPresent);

/**
 * Has the page/PTE been referenced "recently"?
 *
 * @return true if PTE reference "bit" is set.
 */
bool PTE::referenced() const;

/**
 * Set the referenced "bit" in the PTE
 *
 * @param newReferenced new value of referenced bit
 * @return value of represented after it is set
 */
bool PTE::referenced(bool newReferenced);
