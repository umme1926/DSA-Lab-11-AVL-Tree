#include <iostream>      
using namespace std;     

// FOR NODE OF AVL TREE
struct Node
{
    int data;            // TO STORE VALUE IN NODE
    Node* left;          // ADDRESS OF LEFT CHILD
    Node* right;         // ADDRESS OF RIGHT CHILD
    int height;          // HEIGHT OF NODE
};

// TO FIND MAXIMUM FROM TWO NUMBERS
int max(int a, int b)
{
    
    if (a > b)
    {
        return a;   // a RETURN
    }
    else
    {
        return b;   // b RETURN
    }

}

// TO FIND THE HEIGHT OF NODE
int height(Node* n)
{
    // FOR NULL NODE
    if (n == NULL)
        return 0;

    // NODE'S HEIGHT RETURN
    return n->height;
}

// TO CREATE NEW NODE
Node* createNode(int value)
{
    Node* newNode = new Node();   // ALLOCATE MEMORY

    newNode->data = value;        // PUT VALUE IN NODE
    newNode->left = NULL;         
    newNode->right = NULL;        
    newNode->height = 1;          

    return newNode;               // TO RETURN THE ADDRESS OF NODE
}

// RIGHT ROTATION(LEFT-LEFT CASE)
Node* rightRotate(Node* y)
{
    Node* x = y->left;            
    Node* T2 = x->right;          // TO STORE THE RIGHT SUBTREE OF x 

    // TO PERFORM ROTATION
    x->right = y;                 
    y->left = T2;                 

    // UPDATE THE HEIGHTS
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;                     // TO RETURN NEW ROOT
}

// LEFT ROTATION (RIGHT-RIGHT CASE)
Node* leftRotate(Node* x)
{
    Node* y = x->right;           
    Node* T2 = y->left;           // SAVE THE LEFT SUBTREE OF y

    // TO PERFORM ROTATION
    y->left = x;                  
    x->right = T2;                

    // UPDATE HEIGHTS
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;                     // RETURN NEW ROOT
}

// GET BALANCE FACTOR
int getBalance(Node* n)
{
    // FOR NULL NODE
    if (n == NULL)
        return 0;

    return height(n->left) - height(n->right);
}

// INSERTION IN AVL TREE
Node* insert(Node* node, int value)
{
    // MAKE NEW NODE IF TREE IS EMPTY
    if (node == NULL)
        return createNode(value);

    // FOLLOW THE RULES OF BST
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
        return node;   

    // TO UPDATE THE HEIGHT
    node->height = 1 + max(height(node->left), height(node->right));

    // GET BALANCE FACTOR
    int balance = getBalance(node);

    // LEFT-LEFT CASE
    if (balance > 1 && value < node->left->data)
        return rightRotate(node);

    // RIGHT-RIGHT CASE
    if (balance < -1 && value > node->right->data)
        return leftRotate(node);

    // LEFT-RIGHT CASE
    if (balance > 1 && value > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RIGHT-LEFT CASE
    if (balance < -1 && value < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;   
}

// INORDER TRAVERSAL
void inorder(Node* root)
{
    // IF ROOT IS NOT NULL
    if (root != NULL)
    {
        inorder(root->left);      // PRINT LRFT SUBTREE
        cout << root->data << " "; // PRINT ROOT
        inorder(root->right);     // PRINT RIGHT SUBTREE
    }
}

// MAIN FUNCTION
int main()
{
    Node* root = NULL;            // START THE ROOT FROM NULL
    int choice, value;

    do
    {
        // MAIN MENU
        cout << "\n\n--- AVL TREE MENU ---\n";
        cout << "1. INSERT NODE\n";
        cout << "2. DISPLAY INORDER TRAVERSAL\n";
        cout << "3. EXIT\n";
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "ENTER VALUE TO INSERT: ";
            cin >> value;
            root = insert(root, value);  // INSERT VALUE
            cout << "VALUE INSERTED SUCCESSFULLY!";
            break;

        case 2:
            cout << "INORDER TRAVERSAL: ";
            inorder(root);               // TO DISPLAY TREE
            break;

        case 3:
            cout << "EXITING PROGRAM...";
            break;

        default:
            cout << "INVALID CHOICE!TRY AGAIN";
        }

    } while (choice != 3);  

    return 0;               
}
