#include <stdio.h>
#include <stdlib.h>

// Define the structure of each node of the list
struct aNode {
    int nodeValue;          // nodeValue contains the value of the node
    struct aNode *nextNode; // nextNode ontains the address of the next node
};

// Define 'Node' as a synonym of 'struct aNode'
// So wherever there is 'Node' means 'struct aNode'
typedef struct aNode Node;

Node *head; // Declare head that points to the first node of the list

void insertNode( int insertValue ); // Inserts a value in the node in sorted way
void deleteNode( int deleteValue ); // Deletes a value from the list
void printList();                   // Prints the whole list
int instructions();                 // Show a set of instructions, what you want to do

int main()
{
    head = NULL;   // The head points to nothing, indicating the list has not been created yet

    int input, choice;

    do {
        choice = instructions();    // Take choice from the user
        if( choice == 1 ) {         // If user wants to insert a node
            printf( "Enter the value: " );
            scanf( "%d", &input );  // Take the value to be inserted
            insertNode( input );    // Send the value to the insertNode function
        }
        else if( choice == 2 ) {    // If user wants to delete a node
            printf( "Enter the value: " );
            scanf( "%d", &input );  // Take the value to be deleted
            deleteNode( input );    // Send the value to the deleteNode function
        }
        else if( choice != 3 ) {    // If choice is invalid
            printf( "\n" );
            printf( "Invalid choice. Choose again.\n\n" );
        }
    } while( choice != 3 );         // Run until choice is Quit (3)

    return 0;
}

int instructions()
{
    int option;
    printf( "1. Insert a value in the list\n"   ); // Brackets are aligned for
    printf( "2. Delete a value from the list\n" ); // beautification purpose
    printf( "3. Quit program\n"                 ); // only :P :P :P
    printf( "Enter your option: "               );
    scanf ( "%d", &option                       );
    return option;  // Return the value of the option that user wants to do
}

void insertNode( int insertValue )
{
    Node *temp;     // Pointer to the newly created node
    Node *current;  // Pointer required to run the loop

    temp = ( Node * ) malloc( sizeof( Node ) ); // Allocate memory for a new node
    temp->nodeValue = insertValue;              // Give nodeValue the value from the user
    temp->nextNode = NULL;                      // The nextNode pointer points to nothing yet

    if( !head ) {       // If the list is empty, i.e. no entry yet
        head = temp;    // Give head the address of the newly created node
    }
    else if( insertValue <= head->nodeValue ) {
        // If the value to be inserted is less than or equal to the value which is at the start
        // of the list then, the new node will be the head and the nextNode of the new head
        // will point to the previous head, which is now the second node.
        temp->nextNode = head;
        head = temp;    // The newly created node is head now
    }
    else {
        // The loop will go through the whole list and will stop only if the two nodes are found
        // for which the insertValue is greater than previous one, and less than or equal to
        // the next one. So the value will be inserted between them.
        // If the value is greater than all the existing nodes i.e. no two nodes are found
        // as mentioned above, then the new node will be inserted at the end of the list.
        for( current = head; current->nextNode; current = current->nextNode ) {
            if( insertValue > current->nodeValue && insertValue <= current->nextNode->nodeValue )
                break;      // Break the loop if the position for insertion is found
        }

        if( !( current->nextNode ) )    // If current-nextNode is NULL i.e. no position found for
            current->nextNode = temp;   // insertion then, insert the new node at the end.

        else {      // The new node will be inserted between current and current->nextNode
            temp->nextNode = current->nextNode;
            current->nextNode = temp;
        }
    }

    printf( "\n" );
    printf( "Value has been inserted successfully!\n" );
    printList();    // Print the updated list

    return;
}

void deleteNode( int deleteValue )
{
    if( !head ) {                               // If no list available
        printf( "\n" );
        printf( "No node available yet.\n\n" ); // Show error message
        return;
    }

    Node *current, *temp;

    // If the deleteValue is at the head node
    if( deleteValue == head->nodeValue ) {
        temp = head;    // Store the address to free the memory later
        head = head->nextNode;
        free( temp );
    }

    else {
        // The loop will go through the whole list and will stop only if the node
        // with the provided value to be deleted is found.
        for( current = head; current->nextNode; current = current->nextNode ) {
            if( current->nextNode->nodeValue == deleteValue )
                break;  // Break the loop if the value to be deleted is found
        }

        if( !current->nextNode ) {                              // If the value was not found
            printf( "\n" );
            printf( "The value was not found in the list.\n\n" ); // then, print not found report.
            return;
        }

        // Otherwise, i.e. the value is found at current->nextNode
        temp = current->nextNode;   // Store the address to free the memory later
        current->nextNode = current->nextNode->nextNode;
        free( temp );
    }

    printf( "\n" );
    printf( "The node has been deleted!\n" );
    printList();    // Print the updated list

    return;
}

void printList()
{
    Node *current;

    if( !head ) {                               // If no node available
        printf( "No node available.\n\n" );     // show error message
        return;                                 // and return.
    }

    // otherwise
    printf( "Here is the updated list:\n" );

    // Loop through the list and print the values
    for( current = head; current; current = current->nextNode )
        printf( "%d --> ", current->nodeValue );
    printf( "NULL\n\n" );

    return;
}
