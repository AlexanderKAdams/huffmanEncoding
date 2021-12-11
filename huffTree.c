/*
 * Author: Alex Adams
 */

#include <malloc.h>
#include <stdlib.h>
#include "treeNode.h"

struct TreeNode * createTreeNode(unsigned char data, unsigned long freq, unsigned char symbol)
{
  struct TreeNode *node = malloc(sizeof(struct TreeNode));
  node->data=data;
  node->freq=freq;
  node->symbol=symbol;
  node->symlen=0;
  node->left=node->right=NULL;
  return node;
}

int maxDepth(struct TreeNode* root)
{
  if(root==NULL) return 0;
  return max(maxDepth(root->right), maxDepth(root->left))+1;
}

int max(int num1, int num2)
{
  if(num1>num2) return num1;
  return num2;
}

unsigned char minValue(struct TreeNode *pNode)
{
  struct TreeNode* current = pNode;
  while(current->left!=NULL) current= current->left;
  return current->data;
}

void printIt(struct TreeNode* root)
{
  if(root!=NULL)
  {
    printIt(root->left);
    printf("%c ", root->data);
    if(root->right)
      printIt(root->right);
  }
}

void printLeaves(struct TreeNode* root)
{
  if(root!=NULL)
  {
    printf("Symbol\tFreq\tCode");
    doItForTheNewline(root);
  }
  printf("\n");
}

void doItForTheNewline(struct TreeNode* root)
{
  if(root->right==NULL&&root->left==NULL)
  {
    unsigned i;
    unsigned char data;
    data = root->data;
    if(data < 33 || data > 126) printf("\n=%d\t", data);
    else printf("\n%c\t", data);
    printf("%lu\t", root->freq);
    for (i = 1 << 31; i > 0; i = i / 2)
    {
      if (root->symbol & i)
      {
        printf("1");
      }
      else printf("0");
    }
  }
  else if(root->left!=NULL) doItForTheNewline(root->left);
  if(root->right!=NULL) doItForTheNewline(root->right);
}

void verboseNewline(struct TreeNode *pNode, int line)
{
  printf("(%c,%d) ", pNode->data, line);
  if(pNode->left!=NULL) verboseNewline(pNode->left, line+1);
  if(pNode->right!=NULL) verboseNewline(pNode->right, line+1);
}

void freeTree(struct TreeNode* root)
{
  struct TreeNode* left = root->left;
  struct TreeNode* right = root->right;
  if(left!=NULL) freeTree(left);
  if(right!=NULL) freeTree(right);
  free(root);
}

/* pretty much 100% taken from geeksforgeeks because count should be easy but
 * I wasn't remembering it rn */
unsigned long countLeaves(struct TreeNode* pNode)
{
  if(pNode == NULL) return 0;
  if(pNode->left == NULL && pNode->right==NULL) return 1;
  else
    return countLeaves(pNode->left)+countLeaves(pNode->right);
}