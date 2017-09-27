#include <stdlib.h>
#include <stdio.h>

/* A stack implemented in the form of a linked list */

//Node structure
typedef struct node
{
  struct node *next;
  int data;
}node;


//Callback definition for traversal of list.
typedef void (*callback)(node* data);


//Create a new node and return a pointer to it.
node* create( int data )
{
  node* new_node = (node*)malloc( sizeof(node) );
  if(new_node == NULL)
  {
      printf("Error with creating new node with data %d.\n", data);
      exit(0);
  }
  new_node->next = NULL;
  new_node->data = data;
  return new_node;
}


//Push: Adds a node on top of the stack and returns a point to it.
node* push( node* head, int data )
{
  node* new_node = create(data);
  new_node->next = head;
  return new_node;
}


//Pop: Removes the head of the stack and returns the new head.
node* pop( node* head )
{
  node* new_head = head->next;
  free(head);
  return new_head;
}


//Deletes stack
node* delete_stack( node* head )
{
  while(head != NULL)
  {
    head = pop(head);
  }
  return head;
}


//Traverses the list
void traverse( node* head, callback f )
{
  node* cursor = head;
  while( cursor != NULL )
  {
    f(cursor);
    cursor = cursor->next;
  }
  return;
}


//Prints a node's data out
void print_node( node* n )
{
  if(n != NULL){
    printf("  %d  \n", n->data);
  }
  return;
}


//Main
int main(void)
{
  char str;
  int data;
  node* head = NULL;
  printf("\n");
  printf("Push: a | Pop: b | Print List: c | Delete Stack: d \n");
  while(1)
  {
    scanf("%c", &str);

    switch(str)
    {
      case 'a':
        printf("Data:\n");
        scanf("%d", &data);
        head = push( head, data);
        printf("Pushed: %d\n", data);
        printf("\n");
        printf("Push: a | Pop: b | Print List: c | Delete Stack: d \n");
        break;

      case 'b':
        head = pop( head );
        printf("Popped, New head: %d\n", head->data);
        printf("\n");
        printf("Push: a | Pop: b | Print List: c | Delete Stack: d \n");
        break;

      case 'c':
        printf("\n");
        printf("-----\n");
        traverse( head, print_node );
        printf("-----\n");
        printf("\n");
        printf("Push: a | Pop: b | Print List: c | Delete Stack: d \n");
        break;

      case 'd':
        head = delete_stack(head);
        printf("Stack deleted\n");
        printf("\n");
        printf("Push: a | Pop: b | Print List: c | Delete Stack: d \n");
    }
  }
  return 0;
}
