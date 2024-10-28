#include "list.h"
#include "stdlib.h"
#include "stdio.h"

Node* ListCreateNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) perror("Function 'ListCreateNode' could not allocate memory");
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void ListInsertFront(Node **head, int data)
{
    Node* newNode = ListCreateNode(data);
    newNode->next = *head;
    *head = newNode;
}

void ListInsertBack(Node **head, int data)
{
    Node *newNode = ListCreateNode(data);
    Node *currentNode = *head;

    while (currentNode->next)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

int ListPopFront(Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return -1;
    }

    Node *temp = *head;
    int data = temp->data;

    *head = temp->next;
    free(temp);
    temp = NULL;

    return data;
}

int ListPopBack(Node **head)
{
    if (*head == NULL) {
        printf("List is empty \n");
        return -1;
    }

    Node *currentNode = *head;
    while (currentNode->next->next)
    {
        currentNode = currentNode->next;
    }

    int data = currentNode->next->data;
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
        printf("[%d] ", currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}