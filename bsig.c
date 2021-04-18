// bsig.c ... functions on Tuple Signatures (bsig's)
// part of signature indexed files
// Written by John Shepherd, March 2019

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "bsig.h"
#include "psig.h"
void findPagesUsingBitSlices(Query q)
{
	assert(q != NULL);
	//TODO
	Bits qsig = makePageSig(q->rel, q->qstring);
	setAllBits(q->pages);
	PageID curpid = -1; Page bsigp; Offset bi;
	for (Offset i = 0; i < psigBits(q->rel); i++) {
		// printf("nsigpage = %d\n",q->nsigpages);
		if (bitIsSet(qsig, i)) {
			// Slice = get i'th bit slice from bsigFile
			Bits slice = newBits(bsigBits(q->rel));
			PageID bsigpid = i / maxBsigsPP(q->rel);
			bsigp = getPage(bsigFile(q->rel), bsigpid);
			if (curpid != bsigpid) {
				curpid = bsigpid;
				q->nsigpages++;
			}
			q->nsigs++;
			bi = i % maxBsigsPP(q->rel);
			getBits(bsigp, bi, slice);
			// zero bits in pages which are zero in slice
			// showBits(q->pages); printf ("\n");
			// printf("# pages: %d | psig length: %d | bit-slice length: %d\n", nPages(q->rel), psigBits(q->rel), bsigBits(q->rel));
			// andBits(q->pages, slice);
			for (int si = 0; si < nPages(q->rel); si++) {
				if (bitIsSet(slice, si)) continue;
				unsetBit(q->pages, si);
			}
			freeBits(slice);
			free(bsigp);
		}
	}
	freeBits(qsig);
	// printf("Matched Pages:"); showBits(q->pages); putchar('\n');
}