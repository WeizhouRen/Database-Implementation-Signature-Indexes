// psig.c ... functions on page signatures (psig's)
// part of signature indexed files
// Written by John Shepherd, March 2019

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "psig.h"
#include "tsig.h"

// roughly half the bits are set in each signature when the page is full. 
// Since the signatures are coming from c tuples, the bits per codeword 
// value should be divided by this value (c). 
Bits makePageSig(Reln r, Tuple t)
{
	assert(r != NULL && t != NULL);
	//TODO
	// printf ("tsig len: %d | psig len: %d\n", tsigBits(r), psigBits(r));
	Bits psig = newBits(psigBits(r));
	// Count u = psigBits(r) / maxTupsPP(r);
	char **tuplevals = tupleVals(r, t);
	Count shifted = 0;
	for (int i = 0; i < nAttrs(r); i++) {
		Count u = psigBits(r) / nAttrs(r);
		if (i == 0) u += psigBits(r) % nAttrs(r);
		Bits cw = newBits(psigBits(r));
		if (strcmp(tuplevals[i], "?") != 0) {
			cw = sigType(r) == 's' ? genCodeword(tuplevals[i], psigBits(r), psigBits(r), codeBits(r)) 
				: genCodeword(tuplevals[i], psigBits(r), u, codeBits(r));
		}
		// printf("codeword:	"); showBits(cw); printf("\n");
		if (sigType(r) == 'c') {
			shiftBits(cw, shifted);
			shifted += u;
		}
		// printf("shifted:	"); showBits(cw); printf("\n");

		orBits(psig, cw);
		// printf("psig:		"); showBits(psig); printf("\n");
		freeBits(cw);
	}
	// printf("shifted : %d\n", shifted);
	free(tuplevals);
	return psig;
}

void findPagesUsingPageSigs(Query q)
{
	assert(q != NULL);
	//TODO
	Bits qsig = makePageSig(q->rel, q->qstring);
	unsetAllBits(q->pages);
	// Iterate pages of psig file to get each page
	for (int pid = 0; pid < nPsigPages(q->rel); pid++) {
		Page psigp = getPage(psigFile(q->rel), pid);
		// Iterate psigs in page psigp to get each psig
		for(int psigid = 0; psigid < pageNitems(psigp); psigid++) {
			Bits psig = newBits(psigBits(q->rel));
			getBits(psigp, psigid, psig);
			// if query sig match page sig, set q->pages
			if (isSubset(qsig, psig)) {
				Offset datapid = psigid + pid * maxPsigsPP(q->rel);
				setBit(q->pages, datapid);
			}
			freeBits(psig);
			q->nsigs++;
		}
		free(psigp);
		q->nsigpages++;
	}
	freeBits(qsig);
	// printf("Matched Pages:"); showBits(q->pages); putchar('\n');
}

