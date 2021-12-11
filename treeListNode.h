/*
 * Author: Alex Adams
 */

#ifndef HUFFMANENCODING_TREELISTNODE_H
#define HUFFMANENCODING_TREELISTNODE_H
#include "treeNode.h"
struct ListNode
{
  struct TreeNode* data;
  struct ListNode* next;
  struct ListNode* previous;
};

/* Alloc a new node with given data. */
struct ListNode *createNode(struct TreeNode *data);

/* Insert treeNode at appropriate place in a sorted list, return new list head. */
struct ListNode* insertSorted(struct ListNode* head, struct TreeNode *treeNode);

/* Treat list as a stack. (LIFO - last in, first out)
 * Remove and return data from head of non-empty list, changing head.
 * Memory for removed node should be freed. */
struct TreeNode * popStack(struct ListNode** headRef);

/* Return length of the list. */
int listLength(struct ListNode* head);

/* Free memory used by the list. */
void freeList(struct ListNode* head);

/* Return node with desired value, or NULL if not present */
struct ListNode * has(struct ListNode* head, int data);

#endif /*HUFFMANENCODING_TREELISTNODE_H*/
