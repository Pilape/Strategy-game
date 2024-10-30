#include "list.h"

#include <stdlib.h>
#include <stdio.h>

Node* ListCreateNode(void *data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) perror("Function 'ListCreateNode' could not allocate memory");
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void ListInsertFront(Node **head, void *data)
{
    Node* newNode = ListCreateNode(data);
    newNode->next = *head;
    *head = newNode;
}

void ListInsertBack(Node **head, void *data)
{
    Node *newNode = ListCreateNode(data);
    Node *currentNode = *head;

    while (currentNode->next)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

void* ListPopFront(Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return NULL;
    }

    Node *temp = *head;
    void *data = temp->data;

    *head = temp->next;
    free(temp);
    temp = NULL;

    return data;
}

void* ListPopBack(Node **head)
{
    if (*head == NULL) {
        printf("List is empty \n");
        return NULL;
    }

    Node *currentNode = *head;
    while (currentNode->next->next)
    {
        currentNode = currentNode->next;
    }

    void *data = currentNode->next->data;
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
        printf("[%d] ", *(int*)currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}

PqData* PqGetData(Node *pqNode) { return (PqData*)(pqNode)->data; }

PqData* PqCreateData(int priority, size_t size)
{
    PqData *temp = malloc(sizeof(PqData));
    if (temp == NULL) perror("Faield to allocate memory [Function: PqCreateData]");

    temp->priority = priority;
    temp->data = malloc(sizeof(size));

    return temp;
}

void PqPush(Node **head, PqData *data)
{
    Node* newNode = ListCreateNode(data);

    if (PqGetData(*head)->priority > data->priority)
    {
        newNode->next = *head;
        (*head) = newNode;
        //ListInsertFront(head, newNode);
        return;
    }

    Node* currentNode = *head;

    while (currentNode->next && PqGetData(currentNode->next)->priority < data->priority)
    {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

PqData PqPop(Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return *PqCreateData(-1, 0);
    }

    Node *temp = *head;
    PqData data = *PqGetData(temp);
    *head = temp->next;

    free(temp->data);
    temp->data = NULL;
    free(temp);
    temp = NULL;

    return data;
}

void PqPrint(Node* head)
{
    printf("List: ");
    Node *currentNode = head;

    while (currentNode)
    {
        printf("[%d] ", *(int*)PqGetData(currentNode)->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}