/*
 * Author: Alex Adams
 */

#include <malloc.h>
#include "treeListNode.h"
#include "treeNode.h"

struct ListNode *createNode(struct TreeNode *data)
{
  struct ListNode* node = malloc(sizeof(struct ListNode));
  node -> data = data;
  node -> next = NULL;
  node->previous = NULL;
  return node;
}

int listLength(struct ListNode* head)
{
  struct ListNode* current = head;
  int count = 0;

  while (current != NULL)
  {
    count++;
    current = current->next;
  }
  return count;
}

struct ListNode* insertSorted(struct ListNode* head, struct TreeNode *treeNode)
{
  struct ListNode* newNode;
  struct ListNode* current;
  struct ListNode* lookAhead;

  newNode = createNode(treeNode);

  if(head==NULL)
  {
    return newNode;
  }
  if((head->data)->freq>treeNode->freq)
  {
    newNode->next = head;
    head->previous=newNode;
    return newNode;
  }

  /* If header is higher value, other loops won't apply */
  if(head->data->freq==treeNode->freq&&minValue(treeNode)<minValue(head->data))
  {
    newNode->next=head;
    head->previous=newNode;
    return newNode;
  }

  current = head;
  lookAhead = current -> next;

  while (lookAhead != NULL && (lookAhead->data)->freq < treeNode->freq)
  {
    current = lookAhead;
    lookAhead = lookAhead -> next;
  }

  while(lookAhead!=NULL && (lookAhead->data)->freq == treeNode->freq)
  {
    if(minValue(treeNode) > minValue(lookAhead->data))
    {
      current=lookAhead;
      lookAhead=lookAhead->next;
    }
    else break;
  }

  current -> next = newNode;
  newNode -> previous = current;
  newNode -> next = lookAhead;
  if(lookAhead != NULL) lookAhead -> previous = newNode;

  return head;
}

struct TreeNode * popStack(struct ListNode** headRef)
{
  struct ListNode* remove = *headRef;
  struct ListNode* new = *headRef;
  struct TreeNode* data = remove -> data;
  new = new->next;
  *headRef = new;
  free(remove);
  return data;
}

void freeList(struct ListNode* head)
{
  struct ListNode* next = head->next;
  struct ListNode* current = next;
  free(head);
  while(next!=NULL)
  {
    next = next->next;
    freeTree(current->data);
    free(current);
    current = next;
  }
  free(next);
}

struct ListNode * has(struct ListNode* head, int data)
{
  if(head==NULL || head->data == NULL)
  {
    return NULL;
  }

  while (head != NULL && (head -> data)->data != data)
  {
    head = head -> next;
  }

  if(head!=NULL && (head->data)->data==data)
  {
    return (head);
  }

  return NULL;
}