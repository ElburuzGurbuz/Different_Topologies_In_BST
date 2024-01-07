#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{ 
	int depth;
    int key; 
    struct node *left, *right; 
}BST;

typedef struct Node{
        int data;
        struct Node* next;
        struct Node* down;
}Node;

BST* findSequences(BST *root , Node *list , int size);
BST *newBST(int item);
BST* search(BST* root, int key);
BST* insert(BST* BST, int key);
void insertList(Node **sPtr, int value);
int searchList(Node *head, int key);
void print(Node *head);
int counter =1;
Node *headCases = NULL;
BST *root = NULL;
BST *root2 = NULL;

int main()
{
	Node *printList = NULL;
	char *seq=(char*)malloc(sizeof(char)*600);
	
	printf("Enter the sequence: ");
    scanf("%[^\n]s", seq);
    char *token = (char *)strtok(seq, " ");
    
	int seqlist[atoi(token)];
	root = insert(root,atoi(token));
	root2 = insert(root2,atoi(token));
	int i=1;
	int size=1;
	
	while (token != NULL)
	{
		token = strtok(NULL, " "); 
		if(token !=NULL)
		{
			root = insert(root,atoi(token));
			root2= insert(root2,atoi(token));
			size++;
			i++;
		}
	}
	
	insertList(&headCases , root->key);
	findSequences(root , printList , i);

	return 0;
}

BST* findSequences(BST *root , Node *list , int size)
{
	int length = size;
	int LLSize = linkedListSize(list);
	if(LLSize == length)
	{
		printf("(%d) = ",counter);
		counter++;
		print(list);
		printf("\n");
		return;
	}
	if(root == NULL)
	{
		return;
	}
	
	int option = searchList(list , root->key);
	
	if(option == 0)
	{
		insertList(&list , root->key);
		root =findSequences(root2 , list , length);
	}
	
	if(option == 1)
	{
		findSequences(root->left , list , length);
		findSequences(root->right , list , length);
	}
	return root;
}

int searchList(Node *head, int key)
{
    while (head != NULL)
    {
        if (head->data == key)
        {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

BST *newBST(int item)
{ 
    BST *temp =  (BST *)malloc(sizeof(BST)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
}

BST* insert(BST* BST, int key)
{ 
	if (BST == NULL) 
		return newBST(key); 
		
    if (key <= BST->key) 
        BST->left  = insert(BST->left, key);
        
    else if (key > BST->key) 
        BST->right = insert(BST->right, key);    
  
    return BST; 
} 

BST* search(BST* root, int key)
{ 
    if (root == NULL || root->key == key) 
       return root; 
     
    if (root->key < key) 
       return search(root->right, key); 
  
    return search(root->left, key); 
}

int linkedListSize(Node *head)
{
	int i = 0;
	while(head != NULL)
	{
		head = head->next;
		i++;
	}
	return i;
}

void insertList(Node **sPtr, int value)
{
	Node *newPtr = (Node*)malloc(sizeof(Node));
	newPtr->next= (*sPtr);
	newPtr->data = value;
	(*sPtr) = newPtr;	
}


void print(Node* head) 
{ 
    if (head == NULL) 
	{
		//printf("\n");
		return; 
	}
    print(head->next); 
    printf("%d  ", head->data); 
} 
