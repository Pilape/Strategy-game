#ifndef LIST_H_
#define LIST_H_

#include "raylib.h"

typedef struct Node {

    Vector2 data;
    struct Node *next;

} Node;

#include "stdlib.h"

Node* ListCreateNode(Vector2 data);

void ListInsertFront(Node** head, Vector2 data);
Vector2 ListPopFront(Node** head);

void ListInsertBack(Node** head, Vector2 data);
Vector2 ListPopBack(Node **head);

int ListLength(Node* head);
void ListPrint(Node* head);

/* typedef struct {
    
    void *data;
    int priority;

} PqData;

PqData* PqGetData(Node *pqNode);
PqData* PqCreateData(int priority, size_t size); */

typedef struct _PqNode {

    Vector2 data;
    int priority;
    struct _PqNode *next;

} PqNode;


void PqPush(PqNode **head, Vector2 data, int priority);
Vector2 PqPop(PqNode **head);
void PqPrint(PqNode* head);

#include "raylib.h"
int ListHasVector(Node **head, Vector2 vector);
int PqHasVector(PqNode **head, Vector2 vector);

#endif