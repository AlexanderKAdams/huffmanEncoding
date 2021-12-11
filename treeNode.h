/*
 * Author: Alex Adams
 */


#ifndef HUFFMANENCODING_TREENODE_H
#define HUFFMANENCODING_TREENODE_H

struct TreeNode
{
  unsigned char symbol;
  unsigned long freq;
  unsigned char code;
  unsigned int codelen;
  struct TreeNode* left;
  struct TreeNode* right;
};

/* Alloc a new node with given symbol. */
struct TreeNode * createTreeNode(unsigned char data, unsigned long freq, unsigned char symbol);

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root);

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root);

int max(int num1, int num2);

void printIt(struct TreeNode *root);

void verboseNewline(struct TreeNode *pNode, int line);

unsigned char minValue(struct TreeNode *pNode);

unsigned long countLeaves(struct TreeNode *pNode);

#endif /*HUFFMANENCODING_TREENODE_H */
