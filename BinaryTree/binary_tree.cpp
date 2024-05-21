#include <iostream>
#include <vector>
#include <algorithm> //для sort
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

class BinTree
{
private:
    Node* root;

public:
    int size;

    BinTree() {
        root = nullptr;
        size = 0;
    }

    //Поиск элемента
    int search(int a) {
        if (root = nullptr) {
            return 0;
        }

        Node* node = root;

        while (node != nullptr) {
            if (a == node->data) {
                return 1;
            }
            else if (a < node->data) {
                node = node->left;
            }
            else if (a > node->data) {
                node = node->right;
            }
        }

        return 0;
    }

    //Добавление элемента
    void insert(int a) {
        Node* newNode = new Node;

        newNode->data = a;
        newNode->left = nullptr;
        newNode->right = nullptr;

        Node* node = root;
        Node** nee = &root;

        for (;;) {
            if (node == nullptr) {
                *nee = newNode;
                size++;
                addToVec(*nee);
                return;
            }
            else if (a == node->data) {
                return;
            }
            else if (a < node->data) {
                nee = &node->left;
                node = node->left;
            }
            else if (a > node->data) {
                nee = &node->right;
                node = node->right;
            }
        }
    }

    //Удаление элемента
    int deleteNode(int a) {
        Node* node = root;
        Node** nee = &root;

        for (;;) {
            if (node == nullptr) {
                return NULL;
            }
            else if (a == node->data) {
                break;
            }
            else if (a > node->data) {
                nee = &node->right;
                node = node->right;
            }
            else if (a < node->data) {
                nee = &node->left;
                node = node->left;
            }
        }

        if (node->right == nullptr) {
            *nee = node->left;
        }
        else {
            Node* tempR = node->right;
            if (tempR->left == nullptr) {
                tempR->left = node->left;
                *nee = tempR;
            }
            else {
                Node* tempRL = tempR->left;
                while (tempRL->left != nullptr) {
                    tempR = tempRL;
                    tempRL = tempR->left;
                }

                tempR->left = tempRL->right;
                tempRL->left = node->left;
                tempRL->right = node->right;
                *nee = tempRL;
            }
        }
        size--;
        delFromVec(node->data);
        delete node;
        return 1;
    }

    Node* getRoot() {
        return root;
    }

    int getRootData(Node* node) {
        return node->data;
    }

    //Вектор для вывода элементов
    vector<int> vec;

    void addToVec(Node* node) {
        if (node != nullptr) {
            vec.push_back(node->data);
        }
        sort(vec.begin(), vec.end());
    }

    void delFromVec(int a) {
        for (int i = 0; i < size; i++) {
            if (vec[i] == a) {
                vec.erase(vec.begin() + i);
            }
        }
    }
};

void display(BinTree b, vector<int> a) {
    for (int i = 0; i < b.size; i++) {
        cout << a[i] << "\t";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    BinTree tree;
    int choice;

    cout << "0 - вывод элементов\n"
        << "1 - поиск элемента\n"
        << "2 - добавить элемент\n"
        << "3 - удалить элемент\n"
        << "4 - закончить работу\n";

    do {
        cout << "\nЧто хотите сделать ? : ";
        cin >> choice;
        switch (choice)
        {
        case 0:
            if (tree.size == 0) {
                cout << "Нет элементов" << endl;
            }
            display(tree, tree.vec);
            cout << endl;
            break;
        case 1:
            int number;
            cout << "Введите элемент для поиска: ";
            cin >> number;
            if (tree.search(number) == 0) {
                cout << "Элемент не найден!\n";
            }
            else {
                cout << "Элемент найден!\n";
            }
            break;
        case 2:
            int num;
            cout << "Введите элемент для добавления: ";
            cin >> num;
            tree.insert(num);
            cout << "Элемент добавлен!\n";
            break;
        case 3:
            int delNode;
            cout << "Введите удалаяемый элемент: ";
            cin >> delNode;
            if (tree.deleteNode(delNode) == 1) {
                cout << "Элемент удален!\n";
            }
            else {
                cout << "Не удалось удалить элемент\n";
            }
            break;
        }
    } while (choice != 4);

    return 0;
}