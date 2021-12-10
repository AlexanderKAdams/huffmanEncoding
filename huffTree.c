/*
 * Author: Alex Adams
 */

#include <malloc.h>
#include <stdlib.h>
#include "treeNode.h"

struct TreeNode * createTreeNode(char data, unsigned long freq, char symbol)
{
  struct TreeNode *node = malloc(sizeof(struct TreeNode));
  node->data=data;
  node->freq=freq;
  node->symbol=symbol;
  node->left=node->right=NULL;
  return node;
}

struct TreeNode * removeNode(struct TreeNode **rootRef);

struct TreeNode * removeNode(struct TreeNode **rootRef)
{
  struct TreeNode* node = *rootRef;
  struct TreeNode* tmp;
  if(node->right==NULL&&node->left==NULL)
  {
    free(node);
    return NULL;
  }
  else if(node->right==NULL)
  {
    tmp = *rootRef;
    *rootRef = node->left;
    free(tmp);
    return *rootRef;
  }
  else if(node->left==NULL)
  {
    tmp = *rootRef;
    *rootRef = node->right;
    free(tmp);
    return *rootRef;
  }
  else
  {
    tmp=node;
    node=node->left;
    node->right=tmp->right;
    free(tmp);
    return node;
  }
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

char minValue(struct TreeNode *pNode)
{
  struct TreeNode* current = pNode;
  while(current->left!=NULL) current= current->left;
  return current->data;
}

void printTree(struct TreeNode* root)
{
  if(root!=NULL)
  {
    printIt(root);
  }
  printf("\n");
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
    char bool;
    unsigned char symbol;
    symbol = root->symbol;
    bool = 0;
    if(symbol<33||symbol>126) printf("=%d\t",symbol);
    else printf("%c\t", symbol);
    printf("%lu\t", root->freq);
    for (i = 1 << 31; i > 0; i = i / 2)
    {
      if (root->symbol & i)
      {
        printf("1");
        bool=1;
      }
      else if (bool) printf("0");
    }
  }
  else if(root->left!=NULL) doItForTheNewline(root->left);
  if(root->right!=NULL) doItForTheNewline(root->right);
}

void printTreeVerbose(struct TreeNode* root)
{
  if(root!=NULL)
  {
    verboseNewline(root, 1);
  }
  printf("\n");
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