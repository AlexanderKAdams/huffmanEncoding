/*
 * Author: Alex Adams
 */

#include <malloc.h>
#include "listNode.h"
#include "treeNode.h"

struct ListNode * createNode(struct TreeNode *data, long freq, char symbol)
{
  struct ListNode* node = malloc(sizeof(struct ListNode));
  node -> data = data;
  node -> next = NULL;
  node->previous = NULL;
  return node;
}

void printList(struct ListNode* head) //TODO fix or delete
{
  struct ListNode* current = head;
  if(head==NULL)
  {
    printf("\n");
    return;
  }
  while(current->next!=NULL)
  {
    printf("%c, ", current -> data);
    current = current->next;
  }
  printf("%c",current->data);
  printf("\n");
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

  newNode = createNode(treeNode, 0, 0);

  if(head==NULL)
  {
    return newNode;
  }
  if((head->data)->freq>treeNode->freq)
  {
    newNode->next = head;
    return newNode;
  }
  current = head;
  lookAhead = current -> next;

  while (lookAhead != NULL && (lookAhead->data)->freq < treeNode->freq)
  {
    current = lookAhead;
    lookAhead = lookAhead -> next;
  }

  current -> next = newNode;
  newNode -> previous = current;
  newNode -> next = lookAhead;
  lookAhead -> previous = newNode;

  return head;
}

int removeItem(struct ListNode** headRef, char data) // TODO fix or delete
{
  struct ListNode* current = *headRef;
  struct ListNode* previous = *headRef;
  current = current -> next;

  /*
   * if head has data, need to change head
   */

  if(previous->data == data)
  {
    *headRef = current;
    free(previous);
    return 1;
  }

  while(current!=NULL)
  {
    if(current->data == data)
    {
      previous->next = current->next;
      free(current);
      return 1;
    }
    previous=current;
    current=current->next;
  }
  return 0;
}

struct ListNode* pushStack(struct ListNode* head, char data) // TODO fix or
  // delete
{
  struct ListNode* newNode = createNode(data, 0, 0);
  newNode->next = head;
  return newNode;
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

void freeList(struct ListNode* head) // TODO use or delete
{
  struct ListNode* next = head->next;
  struct ListNode* current = next;
  free(head);
  while(next!=NULL)
  {
    next = next->next;
    free(current);
    current = next;
  }
  free(next);
}

void reverseList(struct ListNode** headRef)
{
  struct ListNode* current = *headRef;
  struct ListNode* next;
  struct ListNode* nextNext;
  if(current==NULL) return;
  next = current->next;
  nextNext = next;
  current ->next=NULL;
  while(nextNext!=NULL)
  {
    nextNext = next->next;
    next->next=current;
    current=next;
    next = nextNext;
  }
  *headRef = current;
  free(nextNext);
  free(next);
}

struct ListNode ** has(struct ListNode* head, int data)
{
  struct ListNode* lookAhead;
  if(head==NULL || head->data == NULL)
  {
    return NULL;
  }
  if((head->data)->data>data)
  {
    return NULL;
  }
  lookAhead = head -> next;

  while (lookAhead != NULL && (lookAhead -> data)->data < data)
  {
    lookAhead = lookAhead -> next;
  }

  if((lookAhead->data)->data==data) return (&lookAhead);

  return NULL;
}