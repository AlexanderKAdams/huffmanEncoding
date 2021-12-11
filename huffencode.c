/*
 * Author: Alex Adams
 */

#include <stdio.h>
#include "huffman.h"
#include "treeNode.h"
#include "treeListNode.h"

struct ListNode *charCount(struct ListNode *head, int current);

int main(int argc, char** argv)
{
  char* infile;
  char* outfile;
  FILE* in;
  FILE* out;

  if(argc != 3) 
  {
    printf("wrong number of args\n");
    return 1;
  }

  infile = argv[1];
  outfile = argv[2];

  in = fopen(infile, "rb");
  if(in == NULL)
  {
    printf("couldn't open %s for reading\n", infile);
    return 2;
  }

  out = fopen(outfile, "wb");
  if(out == NULL)
  {
    printf("couldn't open %s for writing\n", outfile);
    return 3;
  }

  encodeFile(in, out);

  fclose(in);
  fclose(out);

  return 0;
}

/* Puts chars into the proper place in the priority queue
 * Dear god this function turned into a monstrosity */
struct ListNode *charCount(struct ListNode *head, int current)
{
  struct ListNode* resultRef;
  struct ListNode* result;
  struct ListNode* next;
  struct TreeNode* ins;
  resultRef = has(head, current);
  if(resultRef != NULL)
  {
    result = resultRef;
    (result->data)->freq++;
    /* While result frequency is higher than next, move it */
    next = result->next;
    while(next!=NULL && (result->data)->freq>(next->data)->freq)
    {
      /* Change head, stupid way to do it, fix if have time */
      if(result->previous == NULL)
      {
        head = result->next;
        result->next=head->next;
        head->next=result;
        head->previous=NULL;
        result->previous=head;
        next=result->next;
        if(result->next!=NULL) result->next->previous=result;
        continue;
      }
      result->next=next->next;
      next->next = result;
      next->previous = result->previous;
      result->previous->next=next;
      result->previous = next;
      next=result->next;
      if(result->next!=NULL) result->next->previous=result;
    }
    /* Tie breaker */
    while(next!=NULL && (result->data)->freq==(next->data)->freq)
    {
      unsigned char minRes;
      unsigned char minNext;

      minRes = minValue(result->data);
      minNext = minValue(next->data);
      if (minRes>minNext)
      {
        result->next=next->next;
        next->next = result;
        next->previous = result->previous;
        if(result->previous!=NULL) result->previous->next=next;
        result->previous = next;
        if(next->previous==NULL) head=next;
        next=result->next;
        if(result->next!=NULL) result->next->previous=result;
      }
      else break;
    }
    return head;
  }

  ins = createTreeNode((char)current, 1, 0);
  head = insertSorted(head, ins);

  return head;
}

struct TreeNode * priqToNode(struct ListNode **pNode);

void codify(struct TreeNode *pNode);


void
tableTime(struct TreeNode *pNode, unsigned long table[256][3]);

void printTable(unsigned long pInt[256][3]);

void
output(unsigned long pInt[256][3], FILE *in, FILE *out, unsigned long count);

void encodeFile(FILE* in, FILE* out)
{
  int current;
  struct ListNode* priq;
  struct TreeNode* treeNode;
  unsigned long counter;
  unsigned long table[256][3] = {0};

  counter = 1;
  current = fgetc(in);
  treeNode = createTreeNode((char)current, 1, 0);
  priq = insertSorted(NULL, treeNode);

  /* put all characters into priority queue */
  while((current = fgetc(in)) != EOF)
  {
    if(current==256) current = 0;
    priq = charCount(priq, current);
    counter++;
  }

  /* Make huffTree from priority queue */
  treeNode = priqToNode(&priq);

  codify(treeNode);

  tableTime(treeNode, table);

  printTable(table);

  freeTree(treeNode);

  output(table, in, out, 0);
}

void output(unsigned long pInt[256][3], FILE *in, FILE *out, unsigned long
count)
{
  int current;
  int i;
  unsigned char howMany;
  unsigned char builder;
  unsigned char tmp;
  int tracker;

  tracker = 8;
  howMany = 0;
  builder = 0;
  tmp = 0;

  for(i=0; i<256; i++)
  {
    if(pInt[i][0]!=0) howMany++;
  }
  /* How many codes exist? Overflow is aight b/c 256=0 anywho */
  fprintf(out,"%c",howMany);
  /* Symbols and codes */
  for(i=0; i<256; i++)
  {
    if(pInt[i][0]!=0)
    {
      fprintf(out, "%c%c%c", i, (unsigned char)pInt[i][2], (unsigned char)
        (pInt[i][1]<<(32-pInt[i][2])));
    }
  }
  /* Print total number of characters encoded */
  fprintf(out, "%lu", count);

  while((current = fgetc(in)) != EOF)
  {
    while(tracker > pInt[current][2])
    {
      builder|=pInt[current][1]<<((8-(8-tracker))-pInt[current][2]);
      tracker-=(int)pInt[current][2];
    }
    if(tracker!=0)
    {
      builder|=pInt[current][1]>>(pInt[current][2]-tracker);
      tmp|=pInt[current][1]<<(8-(pInt[current][2]-tracker));
    }
    fprintf(out, "%c", builder);
    builder = tmp;
    tmp = 0;
    tracker = (int) (8-(pInt[current][2]-tracker));
  }
}

void printTable(unsigned long pInt[256][3])
{
  int i;
  unsigned long j;

  printf("Symbol\tFreq\tCode");

  for(i=0; i<256; i++)
  {
    if(pInt[i][0]!=0)
    {
      if(i < 33 || i > 126) printf("\n=%d\t\t", i);
      else printf("\n%c\t\t", i);
      printf("%lu\t\t", pInt[i][0]);
      for (j = pInt[i][2]; j > 0 ; j--)
      {
        if (pInt[i][1] & (1<<(j-1)))
        {
          printf("1");
        }
        else printf("0");
      }
    }
  }
}

/* Put values in lookup table */
void tableTime(struct TreeNode *pNode, unsigned long table[256][3])
{
  {
    if (pNode->right == NULL && pNode->left == NULL)
    {
      table[pNode->symbol][0] = pNode->freq;
      table[pNode->symbol][1] = pNode->code;
      table[pNode->symbol][2] = pNode->codelen;
    } else if (pNode->left != NULL) tableTime(pNode->left, table);
    if (pNode->right != NULL) tableTime(pNode->right, table);
  }
}

void codify(struct TreeNode *pNode)
{
  if(pNode->right!=NULL)
  {
    pNode->right->code=pNode->code << 1;
    pNode->right->code|=1;
    pNode->right->codelen=pNode->codelen+1;
    codify(pNode->right);
  }
  if(pNode->left!=NULL)
  {
    pNode->left->code=pNode->code << 1;
    pNode->left->codelen=pNode->codelen+1;
    codify(pNode->left);
  }
}

struct TreeNode * priqToNode(struct ListNode **pNode)
{
  int len;
  struct TreeNode* node;
  struct TreeNode* tmp1;
  struct TreeNode* tmp2;

  len = listLength(*pNode);

  while(len>1)
  {
    tmp1 = popStack(pNode);
    tmp2 = popStack(pNode);
    node = createTreeNode(0,(tmp1->freq+tmp2->freq),0);
    node->left=tmp1;
    node->right=tmp2;
    *pNode = insertSorted(*pNode,node);
    len= listLength(*pNode);
  }

  freeList(*pNode);

  return node;
}
