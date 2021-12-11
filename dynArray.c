/*
 * Author: Alex Adams
 * Modified from StackOverflow post by u/casablanca
 */
#include <stddef.h>
#include <malloc.h>
#include "dynArray.h"

void initArray(Array *a, size_t initialSize)
{
  a->data = malloc(initialSize *sizeof(unsigned char));
  a->freq = malloc(initialSize *sizeof(unsigned long));
  a->symbol = malloc(initialSize *sizeof(unsigned char));
  a->symsize = malloc(initialSize *sizeof(unsigned long));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, unsigned char data, unsigned long freq,
                 unsigned char symbol, unsigned long symsize)
{
  if(a->used == a->size)
  {
    a->size*=2;
    a->data = realloc(a->data, a->size * sizeof (unsigned char));
    a->freq = realloc(a->freq, a->size * sizeof (unsigned long));
    a->symbol = realloc(a->symbol, a->size * sizeof (unsigned char));
    a->symsize = realloc(a->symsize, a->size * sizeof (unsigned long));
  }
  a->data[a->used++] = data;
  a->freq[a->used++] = freq;
  a->symbol[a->used++] = symbol;
  a->symsize[a->used++] = symsize;
}

void freeArray(Array *a)
{
  free(a->data);
  a->data=NULL;
  free(a->freq);
  a->freq=NULL;
  free(a->symbol);
  a->symbol=NULL;
  free(a->symsize);
  a->symsize=NULL;
  a->used = a->size = 0;
}

void sort(Array *a)
{

}