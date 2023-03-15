#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void PrintList(Node *curNode)
{
    while (curNode != NULL)
    {
        printf("%d ", curNode->value);
        curNode = curNode->nextNode;
    }
    printf("\n");
    return;
}

void MakeList(Node *head, int value)
{
    head->value = value;
    head->nextNode = NULL;
}

void Add(Node *curNode, int value)
{
    Node *nextNode = (Node*)malloc(sizeof(Node));
    nextNode->value = value;
    nextNode->nextNode = NULL;
    while (curNode->nextNode != NULL)
    {
        curNode = curNode->nextNode;
    }

    curNode->nextNode = nextNode;
    return;
}

int Contains(Node *curNode, int value)
{
    while (curNode != NULL)
    {
        if (value == curNode->value)
        {
            return 1;
        }
        curNode = curNode->nextNode;
    }
    return 0;
}

void Copy(Node *curNode, Node *oldNode)
{
    Node *nextNode;
    
    while (1)
    {
        curNode->value = oldNode->value;
        oldNode = oldNode->nextNode;
        if (oldNode == NULL)
        {
            curNode->nextNode = NULL;
            break;
        }

        nextNode = (Node*)malloc(sizeof(Node));
        curNode->nextNode = nextNode;
        curNode = curNode->nextNode;
    }
    return;
}