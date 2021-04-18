// bits.c ... functions on bit-strings
// part of signature indexed files
// Bit-strings are arbitrarily long byte arrays
// Least significant bits (LSB) are in array[0]
// Most significant bits (MSB) are in array[nbytes-1]

// Written by John Shepherd, March 2019

#include <assert.h>
#include "defs.h"
#include "bits.h"
#include "page.h"

typedef struct _BitsRep {
	Count  nbits;		  // how many bits
	Count  nbytes;		  // how many bytes in array
	Byte   bitstring[1];  // array of bytes to hold bits
	// actual array size is nbytes
} BitsRep;

// create a new Bits object

Bits newBits(int nbits)
{
	Count nbytes = iceil(nbits,8);
	Bits new = malloc(2*sizeof(Count) + nbytes);
	new->nbits = nbits;
	new->nbytes = nbytes;
	memset(&(new->bitstring[0]), 0, nbytes);
	return new;
}

// release memory associated with a Bits object

void freeBits(Bits b)
{
	//TODO
	free(b);
}

// check if the bit at position is 1

Bool bitIsSet(Bits b, int position)
{
	// printf("nbit = %d | position = %d\n", b->nbits, position);
	assert(b != NULL);
	assert(0 <= position && position < b->nbits);
	//TODO
	int byteIdx = position / 8;
	int bitIdx = position % 8;

	if (b->bitstring[byteIdx] & (1 << bitIdx)) return TRUE;
	else return FALSE;
}

// check whether one Bits b1 is a subset of Bits b2

Bool isSubset(Bits b1, Bits b2)
{
	assert(b1 != NULL && b2 != NULL);
	assert(b1->nbytes == b2->nbytes);
	//TODO
	for (int i = 0; i < b1->nbytes; i++) {
		Byte and = b1->bitstring[i] & b2->bitstring[i];
		if ((and != b1->bitstring[i])) return FALSE;
	}
	return TRUE; 
}

// set the bit at position to 1

void setBit(Bits b, int position)
{
	// printf("nbit = %d | position = %d\n", b->nbits, position);
	assert(b != NULL);
	assert(0 <= position && position < b->nbits);
	//TODO
	int byteIdx = position / 8;
	int bitIdx = position % 8;
	b->bitstring[byteIdx] |= 1 << bitIdx;
}

// set all bits to 1

void setAllBits(Bits b)
{
	assert(b != NULL);
	//TODO
	int last_avail = 8 * b->nbytes - b->nbits;
	Byte mask = 0xFF >> last_avail;
	for (int i = 0; i < b->nbytes; i++) {
		b->bitstring[i] |= 0xFF;
		if (i == b->nbytes - 1)
			b->bitstring[i] &= mask;
	}
}

// set the bit at position to 0

void unsetBit(Bits b, int position)
{
	assert(b != NULL);
	assert(0 <= position && position < b->nbits);
	//TODO
	int byteIdx = position / 8;
	int bitIdx = position % 8;
	b->bitstring[byteIdx] &= ~(1 << bitIdx);

}

// set all bits to 0

void unsetAllBits(Bits b)
{
	assert(b != NULL);
	//TODO
	for (int i = 0; i < b->nbytes; i++) {
		b->bitstring[i] |= 0x00;
	}
}

// bitwise AND ... b1 = b1 & b2

void andBits(Bits b1, Bits b2)
{
	assert(b1 != NULL && b2 != NULL);
	assert(b1->nbytes == b2->nbytes);
	//TODO
	for (int i = 0; i < b1->nbytes; i++) {
		b1->bitstring[i] &= b2->bitstring[i];	
	}
}

// bitwise OR ... b1 = b1 | b2

void orBits(Bits b1, Bits b2)
{
	assert(b1 != NULL && b2 != NULL);
	assert(b1->nbytes == b2->nbytes);
	//TODO
	for (int i = 0; i < b1->nbytes; i++) {
		b1->bitstring[i] |= b2->bitstring[i];	
	}
}

// left-shift ... b1 = b1 << n
// negative n gives right shift

void shiftBits(Bits b, int n)
{
	// TODO
	int last_avail = 8 * b->nbytes - b->nbits;
	Byte prev, next, mask = 0xFF >> last_avail;

	// shift bytes
	int byteshifted = n / 8;
	for (int i = b->nbytes - 1; i >= 0; i--) {
		b->bitstring[i] = i >= byteshifted ? b->bitstring[i - byteshifted] : 0x00;
	}
	// shift bits
	n %= 8;
	for (int i = 0; i < b->nbytes; i++) {
		next = b->bitstring[i] >> (8 - n);	// save the left-most n bits
		b->bitstring[i] <<= n;	// left shift bitstring
		b->bitstring[i] |= prev;		// combine with previous left-most n bits
		if (i == b->nbytes - 1) {
			b->bitstring[i] &= mask;
		}
		prev = next;				// update left-most n bits
	}
}
// get a bit-string (of length b->nbytes)
// from specified position in Page buffer
// and place it in a BitsRep structure

void getBits(Page p, Offset pos, Bits b)
{
	//TODO
	Byte* start_addr = addrInPage(p, pos, b->nbytes);
	memcpy(&b->bitstring[0], start_addr, b->nbytes);
}

// copy the bit-string array in a BitsRep
// structure to specified position in Page buffer

void putBits(Page p, Offset pos, Bits b)
{
	//TODO
	Byte* start_addr = addrInPage(p, pos, b->nbytes);
	memcpy(start_addr, &b->bitstring[0], b->nbytes);
}

// show Bits on stdout
// display in order MSB to LSB
// do not append '\n'

void showBits(Bits b)
{
	assert(b != NULL);
	//printf("(%d,%d)",b->nbits,b->nbytes);
	for (int i = b->nbytes-1; i >= 0; i--) {
		for (int j = 7; j >= 0; j--) {
			Byte mask = (1 << j);
			if (b->bitstring[i] & mask)
				putchar('1');
			else
				putchar('0');
		}
	}
}
