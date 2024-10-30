#ifndef LIST_H_
#define LIST_H_

typedef struct Node {

    void *data;
    struct Node *next;

} Node;

#include "stdlib.h"

Node* ListCreateNode(void *data);

void ListInsertFront(Node** head, void *data);
void* ListPopFront(Node** head);

void ListInsertBack(Node** head, void *data);
void* ListPopBack(Node **head);

int ListLength(Node* head);
void ListPrint(Node* head);

typedef struct {
    
    void *data;
    int priority;

} PqData;

PqData* PqGetData(Node *pqNode);
PqData* PqCreateData(int priority, size_t size);

void PqPush(Node **head, PqData *data);
PqData PqPop(Node **head);
void PqPrint(Node* head);

#endif