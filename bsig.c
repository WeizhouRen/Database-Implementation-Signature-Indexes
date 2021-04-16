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
	for (Offset i = 0; i < psigBits(q->rel); i++) {
		if (bitIsSet(q->pages, i)) {
			// Slice = get i'th bit slice from bsigFile
			Bits slice = newBits(bsigBits(q->rel));
			PageID bsigpid = i / maxBsigsPP(q->rel);
			Page bsigp = getPage(bsigFile(q->rel), bsigpid);
			Offset bi = i % maxBsigsPP(q->rel);
			getBits(bsigp, bi, slice);
			orBits(q->pages, slice);
			freeBits(slice);
			free(bsigp);
		}
	}
	freeBits(qsig);
}

