#include "Set.hpp"
#include <iostream>
#include <string>
#include "Vector.hpp"
#include "stack.hpp"
#include "BST.hpp"
#include "Hash.hpp"
#include <sstream>  
using namespace std;


bool isValidXML(const string& s) {
    Stack<string> tags;  // Стек для тегов
    int i = 0, n = s.length();

    while (i < n) {
        if (s[i] == '<') {
            int j = i + 1;
            bool isClosingTag = false;

            if (s[j] == '/') {
                isClosingTag = true;
                j++;
            }

            string tag;
            while (j < n && s[j] != '>') {
                tag += s[j++];  // Собираем имя тега
            }

            if (tag.empty() || (isClosingTag && tags.Empty())) {
                return false;
            }

            if (isClosingTag) {  // Закрывающий тег
                if (tags.Empty() || tags.top() != tag) {
                    return false;
                }
                tags.pop();  // Убираем открывающий тег из стека
            }
            else {  // Открывающий тег
                tags.push(tag);
            }

            i = j + 1;  // Переходим к следующему символу после угловой скобки
        }
        else {
            i++;  // Если не угловая скобка, продолжаем проверку
        }
    }

    return tags.Empty();  // Если стек пуст, XML валиден
}

// Восстановление XML
string restoreXML(string s) {
    // Проходим по всем символам и пытаемся заменить их
    for (int i = 0; i < s.size(); ++i) {
        char originalChar = s[i];

        // Пробуем заменить символ на все возможные буквы латинского алфавита (a-z)
        // и на символы <, >, / (т.к. они могут быть повреждены)
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            s[i] = ch;  // Меняем символ на текущую букву

            if (isValidXML(s)) {
                return s;  // Если строка валидна, возвращаем ее
            }
        }

        // Также пробуем заменить на <, > и /
        for (char ch : {'<', '>', '/'}) {
            s[i] = ch;  // Меняем символ на текущий

            if (isValidXML(s)) {
                return s;  // Если строка валидна, возвращаем ее
            }
        }

        s[i] = originalChar;  // Восстанавливаем исходный символ, если замена не помогла
    }

    return "";  // Если не удалось восстановить строку, возвращаем пустую строку
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

    //делим примерно пополам
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
                    //выводим подмассивы
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
        //рекурсивно обходим (сначала левое поддерево)
        findLeaves(node->left);
        //если у узла нет потомков, это лист
        if (node->left == nullptr && node->right == nullptr) {
            cout << node->data << " "; // Выводим данные листа
        }
        //рекурсивно обходим правое поддерево
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

int countDescendants(const string& name, Map<int>& descendantsCount, Map<string>& tree) {
    // Если количество потомков для этого имени уже вычислено, возвращаем кэшированное значение
    if (descendantsCount.contains(name)) {
        return descendantsCount.get(name);
    }

    int count = 0;

    // Если в дереве есть потомки для этого имени, считаем их количество
    if (tree.contains(name)) {
        string children = tree.get(name); // Получаем строку с детьми
        stringstream ss(children); // Разбиваем строку на детей
        string child;

        // Рекурсивно считаем количество потомков для каждого ребенка
        while (ss >> child) {
            count += 1 + countDescendants(child, descendantsCount, tree); // 1 за ребенка + его потомков
        }
    }

    // Сохраняем количество потомков для этого имени в кэш
    descendantsCount.put(name, count);
    return count;
}

void task6() {
    int N;
    cin >> N;
    cin.ignore();
    string child, parent;

    Map<string> tree;  // Дерево, храним родителя и его детей
    Map<int> descendantsCount;  // Хэш-таблица для подсчета потомков

    // Чтение данных и построение дерева
    for (int i = 0; i < N - 1; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        ss >> child >> parent; // Разбираем пару child-parent
        tree.put(parent, tree.contains(parent) ? tree.get(parent) + child + " " : child + " "); // Добавляем ребенка к родителю
    }

    Set<string> allNames; // Множество для уникальных имен

    // Добавляем имена всех родителей и детей в множество
    for (int i = 0; i < tree.getCap(); ++i) {
        auto current = tree.getData()[i];
        while (current != nullptr) {
            allNames.put(current->key); // Добавляем имя родителя
            stringstream ss(current->value);
            string child;
            while (ss >> child) {
                allNames.put(child); // Добавляем имя ребенка
            }
            current = current->next;
        }
    }

    // Сортируем имена в алфавитном порядке
    Vector<string> allNamesvec = allNames.values();
    allNamesvec.sort();
    // Выводим количество потомков для каждого уникального имени
    cout << "---------------------results:-------------------- " << endl;
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