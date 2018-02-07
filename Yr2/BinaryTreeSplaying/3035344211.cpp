#include <iostream>
using namespace std;

// Node structure for our binary tree
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;
};

// Helpter function to display nodes in inorder traversal
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Helpter function to displya nodes in postorder traversal
void postorder(Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
    }
}

// Helper function to create a new node with a given key and return a pointer to it
Node* newNode(int key) {
    Node *temp = new Node;
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}

// Insert a node into the binary tree
Node* insert(Node *node, int key) {
    // If empty tree, create a new node and return it
    if (node == NULL) {
        return newNode(key);
    }
    // Else insert node by recursion
    if (key < node->key) {
        // Handle left side
        Node *lchild = insert(node->left, key);
        node->left = lchild;
        lchild->parent = node;
    } else if (key > node->key) {
        // Handle right side
        Node *rchild = insert(node->right, key);
        node->right  = rchild;
        rchild->parent = node;
    }
 
    return node;    
}

// Search for a node in a given tree, and pass a counter by reference for num comparisons
Node* search(Node* root, int key, int & counter) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key) {
        counter++;
        return root;
    }
    
    if (root->key < key) {
        // If key is greater than current, move right
        return search(root->right, key, ++counter);
    } else {
        // Else move left
        return search(root->left, key, ++counter);
    }
}    

// Lookup address of a node in tree
Node* lookup(Node* root, int key) {
    if (root == NULL) {
        cout << "Lookup failed" << endl;
    } else if (root->key == key) {
        return root;
    }

    if (root->key < key) {
        return lookup(root->right, key);
    } else {
        return lookup(root->left, key);
    }
}  

// Checks if a given node is a left child of another node
bool isLeftChild(Node *target) {
    if (target->parent == NULL) {
        return false;
    }
    return target->parent->left == target;
}

// Checks if a given node is a right child of another node
bool isRightChild(Node *target) {
    if (target->parent == NULL) {
        return false;
    }
    return target->parent->right == target;
}

// Performs a right rotation on a target node
Node* rightRotation(Node *target) {
    // The target's new left child is it's old left child's right child
    Node *leftChild = target->left; 
    // Case where left child has right child
    if(leftChild->right != NULL) {
        // Set the target's left child to be to current left child's right child
        target->left = leftChild->right; 
        // Set the parent pointer for the nod adjusted in the previous step
        target->left->parent = target;
    } else if (leftChild->right == NULL) {
        target->left = NULL;
    }
    // Set the target to be the child's child
    leftChild->right = target; 
    // Set parent pointer for left child
    if (target->parent != NULL) {
        leftChild->parent = target->parent;
        if (isLeftChild(target)) {
            target->parent->left = leftChild;
        } else {
            target->parent->right = leftChild;
        }        
    } else if (target->parent == NULL) {
        leftChild->parent = NULL;
    }
    // Let the target's parent be the child
    target->parent = leftChild;

    return leftChild; 
}

// Performs a left rotation on a target node
Node* leftRotation(Node *target) {
    // Pick out out target and target's right child for rotation
    Node *rightChild = target->right; 
    // Case where right chld has left child
    if(rightChild->left != NULL) {
        // Set the target's right child to the current right child's left child
        target->right = rightChild->left; 
        // Set the parent pointer for the target's current right child (after last step change)
        target->right->parent = target;        
    } else if (rightChild->left == NULL) {
        target->right = NULL;
    }
    // Switch order of parent and child
    rightChild->left = target; 
    // Set parent for rightChild
    if (target->parent != NULL) {
        rightChild->parent = target->parent;
        if (isLeftChild(target)) {
            target->parent->left = rightChild;
        } else {
            target->parent->right = rightChild;
        }
    } else if (target->parent == NULL) {
        rightChild->parent = NULL;
    }
    // Change parent pointer accordingly for target
    target->parent = rightChild;

    return rightChild; 
}

Node* recursiveSplay(Node *target) {
    if (target->parent == NULL) {
        return target;
    }

    if (isLeftChild(target)) {
        return recursiveSplay(rightRotation(target->parent));
    } else {
        return recursiveSplay(leftRotation(target->parent));
    }
}

// Main driver function
int main () {
    string command; // search, insert, END
    int value; // value passed in (x)
    int costBasic = 0; // cost of basic bst
    int costSplay = 0; // cost of splayed bst

    bool firstInsert = true;

    Node *basicTree = NULL;
    Node *splayTree = NULL;

    // Read in commands until we reach end
    cin >> command;
    while (command != "END") {
        cin >> value;

        if (command == "insert") {
            // Insert into basic and splayed trees
            if (firstInsert) {
                basicTree = insert(basicTree, value);
                splayTree = insert(splayTree, value);
                firstInsert = false;
            } else {
                insert(basicTree, value);  
                insert(splayTree, value);           
            }
            // Modify splay tree after each insert
            splayTree = recursiveSplay(lookup(splayTree, value));
        } else if (command == "search") {
            // Search basic search tree and increment number of comparisons
            search(basicTree, value, costBasic);
            // Search splayed search tree and increment number of comparisons
            search(splayTree, value, costSplay);
            // Modify splay tree after each search
            splayTree = recursiveSplay(lookup(splayTree, value));
        } else {
            cout << "invalid command" << endl;
        }
        cin >> command;
    }
    cout << costBasic << "," << costSplay;

    return 0;
}




