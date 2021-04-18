// tsig.h ... interface to functions on tuple signatures
// part of signature indexed files
// Written by John Shepherd, March 2019

#ifndef TSIG_H
#define TSIG_H 1

#include "defs.h"
#include "query.h"
#include "reln.h"
#include "bits.h"

Bits genCodeword(char *attr_value, int m, int u, int k);
Bits makeTupleSig(Reln, Tuple);
void findPagesUsingTupSigs(Query);

#endif
