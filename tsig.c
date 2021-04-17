// tsig.c ... functions on Tuple Signatures (tsig's)
// part of signature indexed files
// Written by John Shepherd, March 2019

#include <unistd.h>
#include <string.h>
#include "defs.h"
#include "tsig.h"
#include "reln.h"
#include "hash.h"
#include "bits.h"


Bits genCodeword(char *attr_value, int m, int k) 
{
	int nbits = 0;
	Bits cword = newBits(m);
	srandom(hash_any(attr_value, k));
	while (nbits < k) {
		int i = random() % m;
		if (!bitIsSet(cword, i)) {
			setBit(cword, i);
			nbits++; 
		}
	}
	return cword;
}
// make a tuple signature
/**
 * Pesudo code:
	Tsig = AllZeroBits
	for each attribute A in tuple T {
		CW = codeword for A
		Tsig = Tsig OR CW 
	}
 */
Bits makeTupleSig(Reln r, Tuple t)
{
	assert(r != NULL && t != NULL);
	//TODO
	Bits tsig = newBits(tsigBits(r)), cw;
	char **tuplevals = tupleVals(r, t);
	for (int i = 0; i < nAttrs(r); i++) {
		cw = genCodeword(tuplevals[i], tsigBits(r), codeBits(r));
		orBits(tsig, cw);
		freeBits(cw);
	}
	free(tuplevals);
	return tsig;
}

// find "matching" pages using tuple signatures
/**
 * QuerySig = makeTupleSig(Query) 
 * Pages = AllZeroBits
	foreach Tsig in tsigFile {
		if (Tsig matches QuerySig) {
			PID = data page for tuple corresponding to Tsig include PID in Pages
		}
	}
*/
void findPagesUsingTupSigs(Query q)
{
	assert(q != NULL);
	//TODO
	Bits qsig = makeTupleSig(q->rel, q->qstring);
	unsetAllBits(q->pages);	// all zero bits
	// Iterate pages of tsig file
	for (int pid = 0; pid < nTsigPages(q->rel); pid++) {
		Page p = getPage(tsigFile(q->rel), pid);
		// Iterate tsigs in page p to get each tsig in tsigFile
		for (int tid = 0; tid < pageNitems(p); tid++) {
			Bits tsig = newBits(tsigBits(q->rel));
			getBits(p, tid, tsig);	// get current tuple signature
			q->nsigs++;
			if (isSubset(qsig, tsig)) {
				// convert to pageID in data file from pageID in tsig file
				Offset datapid = (tid + pid * maxTsigsPP(q->rel)) / maxTupsPP(q->rel);
				setBit(q->pages, datapid);
			}
			freeBits(tsig);
		}
		free(p);
		q->nsigpages++;
	}
	freeBits(qsig);
	// setAllBits(q->pages); // remove this

	// The printf below is primarily for debugging
	// Remove it before submitting this function
	printf("Matched Pages:"); showBits(q->pages); putchar('\n');
}
