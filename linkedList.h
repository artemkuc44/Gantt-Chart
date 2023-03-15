//Node that holds an integer
typedef struct node
{
    int value;
    struct node *nextNode; 
} Node;

//Prints out a linked list, wasn't used here, but I had it for testing
void PrintList(Node *curNode);

//Takes a pointer and assigns the first value to it
void MakeList(Node *head, int value);

//Adds a node to the back of a list with the given value
void Add(Node *curNode, int value);

//Checks if a list contains a value
int Contains(Node *curNode, int value);

//Copies a list onto a pointer
void Copy(Node *curNode, Node *oldNode);