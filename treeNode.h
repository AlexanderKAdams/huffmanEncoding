//
// Created by aadams on 12/6/21.
//

#ifndef HUFFMANENCODING_TREENODE_H
#define HUFFMANENCODING_TREENODE_H

struct TreeNode
{
  char data;
  unsigned long freq;
  unsigned char symbol;
  struct TreeNode* left;
  struct TreeNode* right;
};

/* Alloc a new node with given data. */
struct TreeNode * createTreeNode(char data, unsigned long freq, char symbol);

/* Insert data at appropriate place in BST, return new tree root. */
struct TreeNode* insertBST(struct TreeNode* root, char data);

/* Remove data from BST pointed to by rootRef, changing root if necessary.
 * For simplicity's sake, always choose node's in-order
 *   predecessor in the two-child case.
 * Memory for removed node should be freed.
 * Return 1 if data was present, 0 if not found. */
int removeBST(struct TreeNode** rootRef, char data);

/* Return maximum value in non-empty binary search tree. */
char maxValueBST(struct TreeNode* root);

/* Return maximum depth of tree. Empty tree has depth 0. */
int maxDepth(struct TreeNode* root);

/* A tree is balanced if both subtrees are balanced and
 * the difference in height between the subtrees is no more than 1.
 * Return 1 if tree is balanced, 0 if not. */
int isBalanced(struct TreeNode* root);

/* Return 1 if tree is a binary search tree, 0 if not. */
int isBST(struct TreeNode* root);

/* Print data for inorder tree traversal on single line,
 * separated with spaces, ending with newline. */
void printTree(struct TreeNode* root);

/* Print data for leaves on single line,
 * separated with spaces, ending with newline.*/
void printLeaves(struct TreeNode* root);

/* Print data for a preorder tree traversal on a single line
 * as a sequence of (data, depth) pairs
 * separated with spaces, ending with newline.
 * (The root node has a depth of 1)
 *
 *  So, the tree
 *
 *      A
 *     / \
 *    B   C
 *   / \
 *  D   E
 *
 * will produce the output
 * (A,1) (B,2) (D,3) (E,3) (C,2)
 */
void printTreeVerbose(struct TreeNode* root);

/* Free memory used by the tree. */
void freeTree(struct TreeNode* root);

int max(int num1, int num2);

void printIt(struct TreeNode *root);

void doItForTheNewline(struct TreeNode *root);

void verboseNewline(struct TreeNode *pNode, int line);

char minValue(struct TreeNode *pNode);

#endif //HUFFMANENCODING_TREENODE_H
