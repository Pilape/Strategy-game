#include "list.h"

#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

Node* ListCreateNode(Vector2 data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) perror("Function 'ListCreateNode' could not allocate memory");
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void ListInsertFront(Node **head, Vector2 data)
{
    Node* newNode = ListCreateNode(data);
    newNode->next = *head;
    *head = newNode;
}

void ListInsertBack(Node **head, Vector2 data)
{
    Node *newNode = ListCreateNode(data);
    Node *currentNode = *head;

    if (*head == NULL) {
        ListInsertFront(head, data);
        return;
    }

    while (currentNode->next)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

Vector2 ListPopFront(Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return (Vector2){0, 0};
    }

    Node *temp = *head;
    Vector2 data = temp->data;

    *head = temp->next;
    free(temp);
    temp = NULL;

    return data;
}

Vector2 ListPopBack(Node **head)
{
    if (*head == NULL) {
        printf("List is empty \n");
        return (Vector2){0, 0};
    }

    Node *currentNode = *head;
    while (currentNode->next->next)
    {
        currentNode = currentNode->next;
    }

    Vector2 data = currentNode->next->data;
    free(currentNode->next);

    currentNode->next = NULL;

    return data;
}

int ListLength(Node* head)
{
    int length = 0;
    Node *currentNode = head;
    
    while (currentNode)
    {
        length++;
        currentNode = currentNode->next;
    }
    
    return length;
}

void ListPrint(Node* head)
{
    printf("List: ");
    Node *currentNode = head;

    while (currentNode)
    {
        printf("[x: %d, y: %d] ", (int)currentNode->data.x, (int)currentNode->data.y);
        currentNode = currentNode->next;
    }
    printf("\n");
}

//PqData* PqGetData(Node *pqNode) { return (PqData*)(pqNode)->data; }

/* PqNode* PqCreateData(int priority, size_t size)
{
    PqData *temp = malloc(sizeof(PqData));
    if (temp == NULL) perror("Faield to allocate memory [Function: PqCreateData]");

    temp->priority = priority;
    temp->data = malloc(sizeof(size));

    return temp;
} */

PqNode *PqCreateNode(Vector2 data, int priority)
{
    PqNode *newNode = malloc(sizeof(PqNode));
    if (newNode == NULL) perror("Function 'ListCreateNode' could not allocate memory");
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    return newNode;
};

void PqPush(PqNode **head, Vector2 data, int priority)
{
    PqNode* newNode = PqCreateNode(data, priority);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if ((*head)->priority > priority)
    {
        newNode->next = *head;
        (*head) = newNode;
        //ListInsertFront(head, newNode);
        return;
    }

    PqNode* currentNode = *head;

    while (currentNode->next && currentNode->next->priority < priority)
    {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

Vector2 PqPop(PqNode **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return (Vector2){0, 0};
    }

    PqNode *temp = *head;
    Vector2 data = temp->data;
    *head = temp->next;

    free(temp);
    temp = NULL;

    return data;
}

void PqPrint(PqNode* head)
{
    printf("List: ");
    PqNode *currentNode = head;

    while (currentNode)
    {
        printf("[x: %f, y: %f] ", currentNode->data.x, currentNode->data.y);
        currentNode = currentNode->next;
    }
    printf("\n");
}

#include "raylib.h"
#include "raymath.h"

int ListHasVector(Node **head, Vector2 vector)
{
    Node* currentNode = *head;
    while (currentNode->next)
    {
        if (Vector2Equals(currentNode->data, vector)) return 1;
        currentNode = currentNode->next;
    }
    
    return 0;
}

int PqHasVector(PqNode **head, Vector2 vector)
{
    if (*head == NULL) return 0;

    PqNode* currentNode = *head;

    while (currentNode->next)
    {
        if (Vector2Equals(currentNode->data, vector)) return 1;

        currentNode = currentNode->next;
    }
    return 0;
}