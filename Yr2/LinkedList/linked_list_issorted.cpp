#include <iostream>
#include <cstdlib>

using namespace std;


struct Node
{
    int key;
    Node *next;
};

void headInsert(Node *&head, int k);
bool isSorted(Node *head);

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

    if(isSorted(head)){
        cout << "Yes";
    }else{
        cout << "No";
    }

}

void headInsert(Node *&head, int k)
{
    Node *newNode = new Node;
    newNode -> key = k;
    newNode -> next = head;
    head = newNode;
}


// Please implement your bool isSorted(Node *head) here...
bool isSorted(Node *head) {
    int previous_val;
    if(head != NULL) {
        previous_val = head->key;
        head = head->next;       
    }
 
    while(head != NULL) {
        if(head->key < previous_val) {
            return false;
        } else {
            previous_val = head->key;
            head = head->next;
        }
    }


    return true;
}