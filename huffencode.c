/*
 * Author: Alex Adams
 */

#include <stdio.h>
#include "huffman.h"
#include "treeNode.h"
#include "treeListNode.h"
#include "dynArray.h"

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

void symbolic(struct TreeNode *pNode);

void
tableTime(struct TreeNode *pNode, Array table);

void encodeFile(FILE* in, FILE* out)
{
  int current;
  struct ListNode* priq;
  struct TreeNode* treeNode;
  Array a;

  current = fgetc(in);
  treeNode = createTreeNode((char)current, 1, 0);
  priq = insertSorted(NULL, treeNode);

  /* put all characters into priority queue */
  while((current = fgetc(in)) != EOF)
  {
    priq = charCount(priq, current);
  }

  /* Make huffTree from priority queue */
  treeNode = priqToNode(&priq);

  symbolic(treeNode);

  initArray(&a, countLeaves(treeNode));

  tableTime(treeNode, a);

  printLeaves(treeNode);

  freeTree(treeNode);
  freeArray(&a);
}

/* I need to put these in a table. The way I do it is horrible, but I have a
 * deadline. */
void tableTime(struct TreeNode *pNode, Array table)
{
  {
    if (pNode->right == NULL && pNode->left == NULL)
    {
      insertArray(&table, pNode->data, pNode->freq, pNode->symbol,
                  pNode->symlen);
    } else if (pNode->left != NULL) tableTime(pNode->left, table);
    if (pNode->right != NULL) tableTime(pNode->right, table);
  }
}

void symbolic(struct TreeNode *pNode)
{
  if(pNode->right!=NULL)
  {
    pNode->right->symbol=pNode->symbol<<1;
    pNode->right->symbol|=1;
    pNode->right->symlen++;
    symbolic(pNode->right);
  }
  if(pNode->left!=NULL)
  {
    pNode->left->symbol=pNode->symbol<<1;
    pNode->left->symlen++;
    symbolic(pNode->left);
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
