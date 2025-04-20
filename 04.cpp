#include <iostream>
using namespace std;

struct Node {
    int key;
    string msg;
    Node* left;
    Node* right;
    
    Node(int k, string value) {
        key = k;
        msg = value;
        left = nullptr;
        right = nullptr;
    }
};

class Dictionary {
public:
    Node* root;

    Dictionary() {
        root = nullptr;
    }

    Node* insert(Node* root, int k, string msg) {
        if (root == nullptr) {
            return new Node(k, msg);
        }
        if (k < root->key) {
            root->left = insert(root->left, k, msg);
        } else if (k > root->key) {
            root->right = insert(root->right, k, msg);
        }
        return root;
    }

    void update(Node* root, int k, string msg) {
        if (!root) {
            cout << "Key not found..\n";
            return;
        }
        if (k < root->key)
            update(root->left, k, msg);
        else if (k > root->key)
            update(root->right, k, msg);
        else
            root->msg = msg;
    }

    Node* search(Node* root, int k, int &count) {
        count = 0;
        while (root != nullptr) {
            count++;
            if (root->key == k)
                return root;
            if (k < root->key)
                root = root->left;
            else
                root = root->right;
        }
        return nullptr;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int k) {
        if (root == nullptr) {
            cout << "Key not found, deletion unsuccessful.\n";
            return root;
        }
        if (k < root->key) {
            root->left = deleteNode(root->left, k);
        } else if (k > root->key) {
            root->right = deleteNode(root->right, k);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                cout << "Key deleted successfully.\n";
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                cout << "Key deleted successfully.\n";
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->msg = temp->msg;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }

    void displayAscending(Node* root) {  
        if (root) {
            displayAscending(root->left);
            cout << root->key << " -> " << root->msg << endl;
            displayAscending(root->right);
        }
    }

    void displayDescending(Node* root) {  
        if (root) {
            displayDescending(root->right);
            cout << root->key << " -> " << root->msg << endl;
            displayDescending(root->left);
        }
    }
};

int main() {
    int choice, k, displayChoice, comparisonCount;
    string msg;
    Dictionary d;
    Node* root = nullptr;

    do {
        cout << "\n1.Insert\n2.Update\n3.Delete\n4.Search\n5.Display\n6.Exit\n";
        cout << "Enter Your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter key (integer) and message: ";
            cin >> k >> msg;
            root = d.insert(root, k, msg);
            cout << "Insertion successful..\n";
        } else if (choice == 2) {
            cout << "Enter key to update: ";
            cin >> k;
            cout << "Enter new message: ";
            cin >> msg;
            d.update(root, k, msg);
            cout << "Update done successfully..\n";
        } else if (choice == 3) {
            cout << "Enter key to delete: ";
            cin >> k;
            root = d.deleteNode(root, k);
        } else if (choice == 4) {
            cout << "Enter key to search: ";
            cin >> k;
            Node* result = d.search(root, k, comparisonCount);
            if (result)
                cout << "Key found! Message: " << result->msg << " (Comparisons: " << comparisonCount << ")\n";
            else
                cout << "Key not found. (Comparisons: " << comparisonCount << ")\n";
        } else if (choice == 5) {
            cout << "\n1. Display in Ascending Order\n2. Display in Descending Order\n";
            cout << "Enter your choice: ";
            cin >> displayChoice;
            if (displayChoice == 1) {
                cout << "\nDictionary in Ascending Order:\n";
                d.displayAscending(root);
            } else if (displayChoice == 2) {
                cout << "\nDictionary in Descending Order:\n";
                d.displayDescending(root);
            } else {
                cout << "Invalid choice!\n";
            }
        } else if (choice == 6) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice! Try again.\n";
        }
    } while (true);

    return 0;
}