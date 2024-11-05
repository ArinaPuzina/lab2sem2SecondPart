#include <iostream>
using namespace std;

struct Node {
    int data;    
    Node* left; 
    Node* right; 

    Node(int val) : data(val), left(nullptr), right(nullptr) {} // ����������� ����
};

// ����� ��� ������������� ��������� ������ ������
struct BST {
    Node* root;//������

    Node* createNode(int data) {
        return new Node(data);
    }

    //����� ��� ������� ���� � ������
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) { //���� ������ ������, ���������� ����� ����
            return createNode(data);
        }

        //�����, ���������� ��������� ������ � ������ �����
        if (data < node->data) {
            node->left = insertNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertNode(node->right, data);
        }

        //���������� ��������� �� ������� ����
        return node;
    }


    //����� ��� ������ ����
    Node* searchNode(Node* node, int key) const {
        if (node == nullptr || node->data == key) {
            return node;
        }

        //���� ���� ������, ���� � ������ ���������
        if (node->data < key) {
            return searchNode(node->right, key);
        }

        // ���� ���� ������, ���� � ����� ���������
        return searchNode(node->left, key);
    }

    // ����� ��� ���������� ������������ ���� � ������ ���������
    Node* minValueNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr) { 
            current = current->left;
        }
        return current;
    }

    // ����� ��� �������� ���� �� ������
    Node* deleteNode(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }

        // ���� ������ ������ �������� ����, ���� � ����� ���������
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        }
        // ���� ������ ������ �������� ����, ���� � ������ ���������
        else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        }
        else { // ���� ������ ��������� � ������� �����
            // ���� � ����� ��� ��� �����
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // ���� � ����� ������: ������� ��������� (������� � ������ ���������)
            Node* temp = minValueNode(root->right);

            // �������� ������ ��������� � ������� ����
            root->data = temp->data;

            // ������� ���������
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    // �����������
    BST() : root(nullptr) {}

    // ����� ��� ������� ���� � ������
    void insert(int data) {
        root = insertNode(root, data);
    }

    // ����� ��� ������ ����
    bool search(int key) const {
        Node* foundNode = searchNode(root, key);
        return foundNode != nullptr;
    }

    // ����� ��� �������� ����
    void deleteValue(int data) {
        root = deleteNode(root, data);
    }
};

