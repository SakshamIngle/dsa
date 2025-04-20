#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string keyword, meaning;
    Node* left;
    Node* right;
    int height;

    Node(string key, string val) {
        keyword = key;
        meaning = val;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, string key, string val) {
    if (!node)
        return new Node(key, val);

    if (key < node->keyword)
        node->left = insert(node->left, key, val);
    else if (key > node->keyword)
        node->right = insert(node->right, key, val);
    else {
        cout << "Keyword already exists. Use update.\n";
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->keyword)
        return rotateRight(node);
    if (balance < -1 && key > node->right->keyword)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->keyword) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->keyword) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, string key) {
    if (!root)
        return root;

    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp)
                root = nullptr;
            else
                *root = *temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    if (!root)
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* update(Node* root, string key, string newMeaning) {
    if (!root)
        return nullptr;

    if (key < root->keyword)
        root->left = update(root->left, key, newMeaning);
    else if (key > root->keyword)
        root->right = update(root->right, key, newMeaning);
    else
        root->meaning = newMeaning;

    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->keyword << " : " << root->meaning << endl;
        inorder(root->right);
    }
}

void reverseInorder(Node* root) {
    if (root) {
        reverseInorder(root->right);
        cout << root->keyword << " : " << root->meaning << endl;
        reverseInorder(root->left);
    }
}

int search(Node* root, string key, int& comparisons) {
    comparisons++;
    if (!root)
        return 0;
    if (key == root->keyword)
        return 1;
    if (key < root->keyword)
        return search(root->left, key, comparisons);
    else
        return search(root->right, key, comparisons);
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\n1. Add\n2. Delete\n3. Update\n4. Display Ascending\n5. Display Descending\n6. Search\n7. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword and meaning: ";
            cin >> key >> meaning;
            root = insert(root, key, meaning);
            break;
        case 2:
            cout << "Enter keyword to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            break;
        case 3:
            cout << "Enter keyword to update: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin >> meaning;
            root = update(root, key, meaning);
            break;
        case 4:
            cout << "Ascending order:\n";
            inorder(root);
            break;
        case 5:
            cout << "Descending order:\n";
            reverseInorder(root);
            break;
        case 6:
            cout << "Enter keyword to search: ";
            cin >> key;
            {
                int comparisons = 0;
                if (search(root, key, comparisons))
                    cout << "Keyword found in " << comparisons << " comparisons.\n";
                else
                    cout << "Keyword not found. Comparisons: " << comparisons << "\n";
                cout << "Max comparisons (height of tree): " << height(root) << endl;
            }
            break;
        }
    } while (choice != 7);

    return 0;
}