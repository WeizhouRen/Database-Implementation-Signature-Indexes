// psig.c ... functions on page signatures (psig's)
// part of signature indexed files
// Written by John Shepherd, March 2019

#include "defs.h"
#include "reln.h"
#include "query.h"
#include "psig.h"
#include "hash.h"

Bits codeword(char *attr_value, int m, int k) 
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

Bits makePageSig(Reln r, Tuple t)
{
	assert(r != NULL && t != NULL);
	//TODO
	Bits psig = newBits(psigBits(r));
	char **tuplevals = tupleVals(r, t);
	for (int i = 0; i < nAttrs(r); i++) {
		Bits cw = codeword(tuplevals[i], psigBits(r), codeBits(r));
		orBits(psig, cw);
		freeBits(cw);
	}
	free(tuplevals);
	return psig;
}

void findPagesUsingPageSigs(Query q)
{
	assert(q != NULL);
	//TODO
	Bits qsig = makePageSig(q->rel, q->qstring);
	unsetAllBits(q->pages);
	for (int pid = 0; pid < nPsigPages(q->rel); pid++) {
		Page psigp = getPage(psigFile(q->rel), pid);
		for(int psigid = 0; psigid < pageNitems(psigp); psigid++) {
			Bits psig = newBits(psigBits(q->rel));
			getBits(psigp, psigid, psig);
			q->nsigs++;
			if (isSubset(qsig, psig)) {
				Offset datapid = psigid + pid * maxPsigsPP(q->rel);
				setBit(q->pages, datapid);
			}
			freeBits(psig);
		}
		free(psigp);
		q->nsigpages++;
	}
}

