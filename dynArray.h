/*
 * Author: Alex Adams
 */

#ifndef HUFFMANENCODING_DYNARRAY_H
#define HUFFMANENCODING_DYNARRAY_H

/* Credit to u/casablanca on StackOverflow for showing how to make a dynamic
 * array. I then made it this unholy abomination. */
typedef struct DynArray
{
  unsigned char *data;
  unsigned long *freq;
  unsigned char *symbol;
  unsigned long *symsize;
  size_t used;
  size_t size;
} Array;

/* Initialize the array to a size */
void initArray(Array *a, size_t initialSize);

/* I probably won't need this, but resize the array if it's ever too large. */
void insertArray(Array *a, unsigned char data, unsigned long freq,
                 unsigned char symbol, unsigned long symsize);

void freeArray(Array *a);

void sort(Array *a);

#endif //HUFFMANENCODING_DYNARRAY_H
