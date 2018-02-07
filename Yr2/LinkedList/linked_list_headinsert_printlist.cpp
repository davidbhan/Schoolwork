#include <iostream>
#include <cstdlib>
using namespace std;


struct Node
{
    int key;
    int value;
    Node *next;
};

void headInsert(Node *&head, int k, int v);
void printList(Node *head);

int main()
{
    Node *head = NULL;

    int n;
    cin >> n;
    int inputK, inputV;
    for (int i=0 ; i< n ; i++)
    {
        cin >> inputK >> inputV;
        cout << inputK << " " << inputV << endl;
        headInsert(head, inputK, inputV);
    }
    printList(head);
}


// Please implement the two functions headInsert() and printList() here.
void headInsert(Node *&head, int k, int v) {
	Node *temp = new Node();
	temp->key = k;
	temp->value = v;
	temp->next = head;
	head = temp;
	return;
}

void printList(Node *head) {
	while(head != NULL) {
		cout << "Key:" << head->key << ",value:" << head->value << endl;
		head = head->next;
	}
	return;
}