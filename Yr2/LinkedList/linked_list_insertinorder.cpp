#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
    int key;
    Node *next;
};

void headInsert(Node *&head, int k); // Given
void printList(Node *head); // Given
void insertInOrder(Node *&head, int k); // Implemented by you

int main()
{
    Node *head = NULL;

    int n;
    cin >> n;
    int inputK;
    for (int i=0 ; i< n ; i++)
    {
        cin >> inputK ;
        headInsert(head, inputK);
    }

    cin >> inputK;
    insertInOrder(head, inputK);

    printList(head);
}

void headInsert(Node *&head, int k)
{
    Node *newNode = new Node;
    newNode -> key = k;
    newNode -> next = head;
    head = newNode;
}

void printList(Node *head)
{
    Node *current = head;
    while (current!=NULL)
    {
        cout << "Key:" << current->key << endl;
        current = current->next;
    }
}

// Please implement void insertInOrder(Node *&head, int k) here.
void insertInOrder(Node *&head, int k) {

    // Case of Empty list
    if (head == NULL) {
        Node *temp = new Node;
        temp->key = k;
        temp->next = NULL;
        return;
    }

    // Case of Insert at head
    if (head->key > k) {
        headInsert(head, k);
    }

    // Keep track of cursor to prevent changing the head pointer (since it's pass by reference)
    Node *cursor = head;
    // Rest of Cases
    while (cursor->key < k) {
        // Check if we've arrived at tail
        if (cursor->next == NULL) {
            Node *temp = new Node;
            temp->key = k;
            temp->next = NULL;
            cursor->next = temp;
            return;
        }
        // Check if we've arrive at the desired place
        if (cursor->next->key > k) {
            Node *temp = new Node;
            temp->key = k;
            temp->next = cursor->next;
            cursor->next = temp;
            return;            
        }
        cursor = cursor->next;
    }

 
}