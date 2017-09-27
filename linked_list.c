#include <stdlib.h>
#include <stdio.h>

/* Basic linked list implemenatation with supported functions for selective deletion and insertion. */


//The structure of a node contains a pointer to the next node in the list and the data
typedef struct node{
  struct node *next;
  int data;
}node;


//Callback function to manupulate a node of the linked list
typedef void (*callback)(node* data);


//Creates a new node and returns it
node* create( int data, node* next)
{
    //Creates the required memory for a new node and returns a pointer to it
    node* new_node = ( node* )malloc( sizeof(node) );

    //If there was a an error with creating the new node
    if( new_node == NULL){
      printf("Error Creating new node. \n");
      exit(0);
    }

    //Sets the value from the pointer location for data
    new_node->data = data;
    new_node->next = next;

    return new_node;
}


//Insert a new node at the start of the list
node* prepend(node* head, int data)
{
  node* new_node = create(data,head);
  head = new_node;
  return head;
}


//Returns a pointer to the last node in the list
node* find_last( node* head )
{
    node* cursor = head;
    while(cursor != NULL)
    {
      if(cursor->next == NULL)
      {
        return cursor;
      }
      cursor = cursor->next;
    }
    printf("Could not find the last element in the list.\n");
    exit(0);
}


//Insert a new node at the end of the list
node* append( node* head, int data )
{
  node* last = find_last(head);
  node* new_node = create(data,NULL);
  last->next = new_node;
  return head;
}


//Traverses the list calling function f on each node
void traverse(node* head, callback f)
{
  node* cursor = head;
  while(cursor != NULL)
  {
      f(cursor);
      cursor = cursor->next;
  }
  return;
}


//Delete the top node from the list
node* delete_head( node* head )
{
    node* new_head = head->next;
    free(head);
    return new_head;
}


//Finds previous node pointer
node* find_previous( node* head, int index )
{
  node* prev_cursor = head;
  node* prev_node = NULL;
  int prev_index = 0;
  //Find the previous node
  while(prev_index <= index-1)
  {
    if(prev_index == index-1)
    {
      prev_node = prev_cursor;
    }
    prev_cursor = prev_cursor->next;
    prev_index++;
  }

  return prev_node;
}


//Deletes the node at the specified index
node* delete_index( node* head, int index )
{
  node* cursor = head;
  int cur_index = 0;
  while(cursor != NULL || cur_index  <= index)
  {
      if(index == cur_index)
      {
          //Case node does exist but is the head
          if(index == 0)
          {
            head = delete_head(head);
            return head;
          }
          //Case node does exist but is the tail
          else if(cursor->next == NULL)
          {
            node* prev_node = find_previous(head, index);
            prev_node->next = NULL;
            free(cursor);
            return head;
          }
          //Case node is in the middle of the list
          else
          {
              node* prev_node = find_previous( head, index );
              //Set the previouses next pointer to point to the one after the deleted node
              prev_node->next = cursor->next;
              //Delete the chosen node
              free(cursor);
              return head;
          }
      }
      //Go to the next node in the list.
      cursor = cursor->next;
      cur_index++;
  }


  //Case node does not exist
  printf("Node to delete at index %d could not be found.\n", index);
  return head;
}


//Counts the number of elements in the linked list
int count(node *head)
{
    node *cursor = head;
    int c = 0;
    while(cursor != NULL )
    {
      c++;
      cursor = cursor->next;
    }
    return c;
}



//Display a node
void display(node* n)
{
    if(n != NULL)
        printf("%d ", n->data);

    return;
}


//main
int main(void)
{
    int data = 5;
    node* head = NULL;
    callback disp = display;

    head = prepend( head, data );
    head = prepend( head, 7 );
    head = append( head, 9);
    head = prepend ( head, 6);
    head = append( head , 2);
    head = append( head, 22 );
    //head = delete_head( head );
    head = delete_index(head, 5);
    traverse( head, disp );
    printf("Number of elements: %d \n", count( head )) ;
}
