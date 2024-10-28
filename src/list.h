#ifndef LIST_H_
#define LIST_H_

typedef struct Node {

    int data;
    struct Node *next;

} Node;

Node* ListCreateNode(int data);

void ListInsertFront(Node** head, int data);
int ListPopFront(Node** head);

void ListInsertBack(Node** head, int data);
int ListPopBack(Node **head);

int ListLength(Node* head);
void ListPrint(Node* head);

#endif