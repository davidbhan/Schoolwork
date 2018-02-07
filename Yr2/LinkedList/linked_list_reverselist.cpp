#include <iostream>
#include <cstdlib>

using namespace std;

struct Node
{
    int key;
    Node *next;
};

void headInsert(Node *&head, int k);
void printList(Node *head);

void reverseList(Node * & head);

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
    printList(head); // Print the list
    reverseList(head); // Reverse the list
    printList(head); // Print the list
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
        cout << "Key:" << current->key  << endl;
        current = current->next;
    }
}

// Implement your void reverseList(Node * & head); function here
void reverseList(Node * & head) {
    // No need to reverse empty lists or lists with single node
    if (head == NULL || head->next == NULL) {
        return;
    }
    Node *pre = NULL;
    Node *next;

    while (head != NULL) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    head = pre;
    return;
}
