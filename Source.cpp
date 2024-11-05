#include "Set.hpp"
#include <iostream>
#include <string>
#include "Vector.hpp"
#include "stack.hpp"
#include "BST.hpp"
#include "Hash.hpp"
#include <sstream>  
using namespace std;
Map<string> tree;  // ������ ��� �������� � ������ ��� �������� (� ���� ������)
Map<int> descendantsCount;  // ���-������� ��� �������� ��������

bool isValidXML(const string& s) {
    Stack<string> tags;//���� �����
    int i = 0, n = s.length();

    while (i < n) {//������������� ��� ������������� ���
        if (s[i] == '<') {
            int j = i + 1;
            bool isClosingTag = false;

            if (s[j] == '/') {
                isClosingTag = true;
                j++;
            }
            string tag;
            while (j < n && s[j] != '>') {
                tag += s[j++];//�������� ��� ����
            }
            if (tag.empty() || (isClosingTag && tags.Empty())) {//���� ��� ���� �� �������
                return false;
            }

            if (isClosingTag) {  // ���� ��� ����������� ���
                if (tags.Empty() || tags.top() != tag) {
                    return false;
                }
                tags.pop();//������� ����������� ��� �� �����
            }
            else { //���� ��� ����������� ���
                tags.push(tag);//�������� ����������� ��� � ����
            }
            i = j + 1; //��������� � ���������� ������� ����� ����������� ������� ������ '>'
        }
        else {
            i++;//���� �� ������ ��������� next ������
        }
    }
    return tags.Empty();
}


    string restoreXML(string s) {
        //�������� ��� ���������� �������, ������������� � ������
        Set<char> validChars;
        for (char ch : s) {
            if (ch != '<' && ch != '>' && ch != '/') {
                validChars.put(ch);
            }
        }
        //������� �������� ������ ������ �� ��� ��������� ������� �� validChars
        for (int i = 0; i < s.size(); ++i) {
            char originalChar = s[i];

            //���������� ������ �������, ������� ����������� � ������
            Vector<char> validCharsVec = validChars.values();
            for (char ch : validCharsVec) {
                s[i] = ch; //�������� ������ �� ������� �� validChars

                if (isValidXML(s)) {
                    return s; //���� ������ ����� ����������, ���������� ��
                }
            }

            s[i] = originalChar; //��������������� �������� ������
        }

        return ""; 
    
}
void task1() {
    string xmlString;
    getline(cin, xmlString);
    string restoredXML = restoreXML(xmlString);
    cout << restoredXML << endl;
}
void task3() {
	Set<int> set;
	set.put(5);
	set.put(8);
	set.put(1);
	set.put(14);
	set.put(7);
	
	Vector<int> helpVec = set.values();
	helpVec.sort();
    helpVec.reverse();
    Vector<int> subsetA;
    Vector<int> subsetB;
    int sumA = 0;
    int sumB = 0;

    //����� �������� �������
    for (int num : helpVec) {
        if (sumA <= sumB) {
            subsetA.pushBack(num);
            sumA += num;
        }
        else {
            subsetB.pushBack(num);
            sumB += num;
        }
    }
    cout << " Set = {" << set << "}" << endl;
    int difference = abs(sumA - sumB);
    cout << "subset A: { ";
    for (int num : subsetA) {
        cout << num << " ";
    }
    cout << "}" << endl;

    cout << "subset B: { ";
    for (int num : subsetB) {
        cout << num << " ";
    }
    cout << "}" << endl;

    cout << "The difference: " << difference << endl;

    
}
void task4() {
        Vector<int> vec;
        vec.pushBack(4);
        vec.pushBack(-7);
        vec.pushBack(1);
        vec.pushBack(5);
        vec.pushBack(-4);
        vec.pushBack(0);
        vec.pushBack(-3);
        vec.pushBack(2);
        vec.pushBack(4);
        vec.pushBack(1);

        int a = 5;
        cout << "Array: " << vec;
        cout << "sum of elements should be " << a<<endl;
        cout << "subarrays: "<<endl;
        for (int i = 0; i < vec.size(); i++) {
            int sum = 0;
            for (int j = i; j < vec.size(); j++) {
                sum += vec.get(j);
                if (sum == a) {
                    //������� ����������
                    for (int k = i; k <= j; k++) {
                        cout << vec.get(k);
                        if (k < j) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
            }
        }
}
void findLeaves(Node* node) {
    if (node != nullptr) {
        //���������� ������� (������� ����� ���������)
        findLeaves(node->left);
        //���� � ���� ��� ��������, ��� ����
        if (node->left == nullptr && node->right == nullptr) {
            cout << node->data << " "; // ������� ������ �����
        }
        //���������� ������� ������ ���������
        findLeaves(node->right);
    }
}

void task5() {
    BST tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(9);
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(0);
    findLeaves(tree.root);
}

//������� ��� �������� �������� � ������� ��������
int countDescendants(const string& name, Map<int>& descendantsCount, Map<string>& tree) {
    if (descendantsCount.contains(name)) {
        return descendantsCount.get(name);//���� ��� ���������, ���������� ���������
    }

    int count = 0;
    if (tree.contains(name)) {
        //�������� ������ �������� ��� �������� ��������
        string children = tree.get(name);//������ � ������� ��������
        stringstream ss(children);//��������� ������ �� ����� ��������
        string child;

        //��� ������� ������� ������� ���������� ��� ��������
        while (ss >> child) {
            count += 1 + countDescendants(child, descendantsCount, tree);
        }
    }

    descendantsCount.put(name, count);
    return count;
}

void task6() {
    int N;
    cin >> N;
    cin.ignore();
    string child, parent;

    Map<string> tree;//������ ��� �������� � ������ ��� �������� (� ���� ������)
    Map<int> descendantsCount;//���-������� ��� �������� ��������

    //������ ������ � ���������� ������
    for (int i = 0; i < N - 1; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        ss >> child >> parent;//��������� �� �������
        tree.put(parent, tree.contains(parent) ? tree.get(parent) + child + " " : child + " "); 
        //��������� �������(������ ��������) � �������� 
    }

    Set<string> allNames; //��������� ��� �������� ���������� ���

    //��������� ����� ���� ��������� � �������� � ������
    for (int i = 0; i < tree.getCap(); ++i) {
        auto current = tree.getData()[i];
        while (current != nullptr) {
            allNames.put(current->key);//��������� ��������
            stringstream ss(current->value);
            string child;
            while (ss >> child) {
                allNames.put(child);//��������� ��������
            }
            current = current->next;
        }
    }
    cout << "---------------------results:-------------------- " << endl;
    //��� ������� �������� ������� ��� ���������� ��������
    Vector<string> allNamesvec = allNames.values();
    allNamesvec.sort();
    for (const string& name : allNamesvec) {
        cout << name << " " << countDescendants(name, descendantsCount, tree) << endl;
    }
}
int main() {
    cout << "-------------------Task 1------------------" << endl;
    task1();
    cout << "-------------------Task 3------------------" << endl;
	task3();
    cout << "-------------------Task 4------------------" << endl;
    task4();
    cout << "-------------------Task 5------------------" << endl;
    task5();
    cout <<endl<< "-------------------Task 6------------------" << endl;
    task6();

}