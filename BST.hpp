#include <iostream>
using namespace std;

struct Node {
    int data;    
    Node* left; 
    Node* right; 

    Node(int val) : data(val), left(nullptr), right(nullptr) {} // Конструктор узла
};

// Класс для представления бинарного дерева поиска
struct BST {
    Node* root;//корень

    Node* createNode(int data) {
        return new Node(data);
    }

    //метод для вставки узла в дерево
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) { //если дерево пустое, возвращаем новый узел
            return createNode(data);
        }

        //иначе, рекурсивно вставляем данные в нужное место
        if (data < node->data) {
            node->left = insertNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertNode(node->right, data);
        }

        //возвращаем указатель на текущий узел
        return node;
    }


    //метод для поиска узла
    Node* searchNode(Node* node, int key) const {
        if (node == nullptr || node->data == key) {
            return node;
        }

        //если ключ больше, идем в правое поддерево
        if (node->data < key) {
            return searchNode(node->right, key);
        }

        // Если ключ меньше, идем в левое поддерево
        return searchNode(node->left, key);
    }

    // Метод для нахождения минимального узла в правом поддереве
    Node* minValueNode(Node* node) const {
        Node* current = node;
        while (current && current->left != nullptr) { 
            current = current->left;
        }
        return current;
    }

    // Метод для удаления узла из дерева
    Node* deleteNode(Node* root, int data) {
        if (root == nullptr) {
            return root;
        }

        // Если данные меньше текущего узла, ищем в левом поддереве
        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        }
        // Если данные больше текущего узла, ищем в правом поддереве
        else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        }
        else { // Если данные совпадают с текущим узлом
            // Узел с одним или без детей
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

            // Узел с двумя детьми: находим преемника (минимум в правом поддереве)
            Node* temp = minValueNode(root->right);

            // Копируем данные преемника в текущий узел
            root->data = temp->data;

            // Удаляем преемника
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    // Конструктор
    BST() : root(nullptr) {}

    // Метод для вставки узла в дерево
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Метод для поиска узла
    bool search(int key) const {
        Node* foundNode = searchNode(root, key);
        return foundNode != nullptr;
    }

    // Метод для удаления узла
    void deleteValue(int data) {
        root = deleteNode(root, data);
    }
};

