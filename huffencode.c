#include <stdio.h>
#include "huffman.h"
#include "treeNode.h"
#include "listNode.h"

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
  struct ListNode** resultRef;
  struct ListNode* result;
  struct ListNode* next;
  struct TreeNode* ins;
  if((resultRef = (has(head, current))) != NULL)
  {
    result = *resultRef;
    (result->data)->freq++;
    /* While result frequency is higher than next, move it */
    next = result->next;
    while((result->data)->freq>(next->data)->freq)
    {
      result->next=next->next;
      next->next = result;
      next->previous = result->previous;
      result->previous = next;
      next=result->next;
    }
    /* Tie breaker */
    while((result->data)->freq==(next->data)->freq)
    {
      char minRes;
      char minNext;

      minRes = minValue(result->data);
      minNext = minValue(next->data);
      if (minRes>minNext)
      {
        result->next=next->next;
        next->next = result;
        next->previous = result->previous;
        result->previous = next;
        next=result->next;
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

void encodeFile(FILE* in, FILE* out)
{
  int current;
  struct ListNode* priq;
  struct TreeNode* treeNode;

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

  printLeaves(treeNode);
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
    node = createTreeNode(-1,(tmp1->freq+tmp2->freq),-1);
    node->left=tmp1;
    tmp1->symbol <<=1;
    node->right=tmp2;
    tmp2->symbol<<=1;
    tmp2->symbol|=1;
    len-=2;
    insertSorted(*pNode,node);
  }

  return node;
}

