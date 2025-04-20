#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

int findHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

int findMinValue(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return -1;
    }
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

void swapTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    swapTree(root->left);
    swapTree(root->right);
}

void displayTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    displayTree(root->left);
    cout << root->data << " ";
    displayTree(root->right);
}


bool searchValue(Node* root, int value) {
    if (root == nullptr) {
        return false;
    }

    if (root->data == value) {
        return true;
    } 
    if (value < root->data) {
        return searchValue(root->left, value);
    } else {
        return searchValue(root->right, value);
    }
}

int main() {
    Node* root = nullptr;
    int choice;
    do{
        cout<<"1.insert\n2.find longest node\n3.minimum data value\n4.change a tree\n5.search value\n6.display\n7.exit\n";
        cout<<"\nEnter Your choice : ";
        cin>>choice;
        if(choice==1){
            int n;
            cout<<"Enter value : ";
            cin>>n;
            root=insertNode(root,n);
            cout<<"Node inserted successfully..\n";
        }else if(choice==2){
            cout << "Height of the tree (Longest path): " << findHeight(root) << endl;
        }else if(choice==3){
            cout << "Minimum value in the tree: " << findMinValue(root) << endl;
        }else if (choice == 4) {
            swapTree(root);
            cout << "Tree has been swapped successfully...\n" << endl;
        }else if(choice==5){
            int s;
            cout<<"Enter search value : ";
            cin>>s;
            if (searchValue(root,s)) {
                cout << "Value " << s << " found in the tree.\n" << endl;
            }else {
                cout << "Value " << s << " not found in the tree.\n" << endl;
            }
        }else if (choice == 6) {
            if (root == nullptr) {
                cout << "Tree is empty.\n" << endl;
            } else {
                cout << "Tree elements (in-order traversal): ";
                displayTree(root);
                cout << endl;
            }
        }else if(choice==7){
            break;
        }else{
            cout<<"\nInvalid choice..\n";
        }
    }while(1);
    return 0;
}