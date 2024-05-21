#include <iostream>
#include <string>
using namespace std;

struct MyData
{
    char surname[20];
    char name[15];
    char lastname[25];

    int day;
    int month;
    int year;

    char address[50];
};

struct Node
{
    MyData data;
    Node* next;
    Node* prev;
};

class LinkedList
{
private:
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    //Добавление элемента в конец списка
    void pushBack(MyData d) {
        Node* newNode = new Node;

        newNode->data = d;
        newNode->next = NULL;

        if (!head) {
            head = tail = newNode;
            newNode->prev = NULL;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    //Добавление элемента в начало списка
    void pushFront(MyData d) {
        if (isEmpty()) {
            pushBack(d);
            return;
        }

        Node* newNode = new Node;

        newNode->data = d;
        newNode->next = head;
        newNode->prev = NULL;
        head->prev = newNode;

        head = newNode;
    }

    //Добавление элемента после элемента с данной позицией
    void insert(MyData d, int pos) {

        if (isEmpty()) {
            pushFront(d);
            return;
        }

        Node* current = head;
        int count = 0;

        while (current) {
            ++count;
            current = current->next;
        }

        if (pos >= count || pos < 0) {
            return;
        }

        if (pos == count - 1) {
            pushBack(d);
            return;
        }

        Node* newNode = new Node;
        newNode->data = d;

        if (pos <= count / 2) {
            current = head;
            for (int i = 0; i <= count / 2; i++) {
                if (pos == i) {
                    newNode->next = current->next;
                    current->next->prev = newNode;
                    newNode->prev = current;
                    current->next = newNode;
                    break;
                }
                else {
                    current = current->next;
                }
            }
        }
        else {
            current = tail;
            for (int i = count - 1; i > count / 2; i--) {
                if (pos == i) {
                    newNode->next = current->next;
                    current->next->prev = newNode;
                    newNode->prev = current;
                    current->next = newNode;
                    break;
                }
                else {
                    current = current->prev;
                }
            }
        }
    }

    //Удаление конечного элемента списка
    void popBack() {
        if (isEmpty()) {
            return;
        }

        Node* delNode = tail;

        if (delNode == head) {
            head = tail = NULL;
            delete delNode;
            return;
        }

        tail = tail->prev;
        tail->next = NULL;
        delete delNode;
    }

    //Удаление начального элемента списка
    void popFront() {
        if (isEmpty()) {
            return;
        }

        Node* delNode = head;

        if (delNode == tail) {
            tail = head = NULL;
            delete delNode;
            return;
        }

        head = head->next;
        head->prev = NULL;
        delete delNode;
    }

    //Удаление элемента с данной позиции
    void popFound(int pos) {
        if (isEmpty() || pos < 0) {
            return;
        }

        if (pos == 0) {
            popFront();
            return;
        }

        Node* dellNode = head;
        int count = 0;

        while (dellNode) {
            ++count;
            dellNode = dellNode->next;
        }

        if (pos >= count) {
            return;
        }

        if (pos == count - 1) {
            popBack();
            return;
        }

        if (pos <= count / 2) {
            dellNode = head;
            for (int i = 0; i < pos; i++) {
                dellNode = dellNode->next;
            }
            dellNode->prev->next = dellNode->next;
            dellNode->next->prev = dellNode->prev;
        }
        else {
            dellNode = tail;
            for (int i = count - 1; i > pos; i--) {
                dellNode = dellNode->prev;
            }
            dellNode->prev->next = dellNode->next;
            dellNode->next->prev = dellNode->prev;
        }

        delete dellNode;
    }

    //Поиск элемента по заданному значению поля структуры
    Node* findDay(int day) {
        if (isEmpty()) {
            return (Node*)NULL;
        }

        Node* current = head;

        while (current) {
            if (current->data.day != day) {
                current = current->next;
            }
            else {
                return current;
            }
        }

        return (Node*)NULL;
    }

    Node* findMonth(int month) {
        if (isEmpty()) {
            return (Node*)NULL;
        }

        Node* current = head;

        while (current) {
            if (current->data.month != month) {
                current = current->next;
            }
            else {
                return current;
            }
        }

        return (Node*)NULL;
    }

    Node* findYear(int year) {
        if (isEmpty()) {
            return (Node*)NULL;
        }

        Node* current = head;

        while (current) {
            if (current->data.year != year) {
                current = current->next;
            }
            else {
                return current;
            }
        }

        return (Node*)NULL;
    }

    Node* findSurname(string surname) {
        if (isEmpty()) {
            return NULL;
        }

        Node* current = head;

        while (current) {
            if (string(current->data.surname).find(surname) != string::npos) {
                return current;
            }
            else {
                current = current->next;
            }
        }

        return NULL;
    }

    Node* findName(string name) {
        if (isEmpty()) {
            return NULL;
        }

        Node* current = head;

        while (current) {
            if (string(current->data.name).find(name) != string::npos) {
                return current;
            }
            else {
                current = current->next;
            }
        }

        return NULL;
    }

    Node* findLastname(string lastname) {
        if (isEmpty()) {
            return NULL;
        }

        Node* current = head;

        while (current) {
            if (string(current->data.surname).find(lastname) != string::npos) {
                return current;
            }
            else {
                current = current->next;
            }
        }

        return NULL;
    }

    Node* findAddress(string address) {
        if (isEmpty()) {
            return NULL;
        }

        Node* current = head;

        while (current) {
            if (string(current->data.address).find(address) != string::npos) {
                return current;
            }
            else {
                current = current->next;
            }
        }

        return NULL;
    }

    //Проверка списка на наличие элементов
    bool isEmpty() {
        if (head) {
            return false;
        }

        return true;
    }

    //Возврат узла с данной позиции
    Node* returnCurrent(int pos) {
        if (pos == 0) {
            return head;
        }

        Node* current = head;
        for (int i = 0; i < pos; i++) {
            current = current->next;
        }

        return current;
    }

    //Вовзрат данных текущего узла
    MyData returnData(Node* a) {
        return a->data;
    }
};

void display(MyData data) {
    cout << data.surname << " " << data.name << " " << data.lastname
        << "  " << data.day << '.' << data.month << '.' << data.year
        << '\n' << data.address << endl << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    LinkedList list;
    int listSize = 0;
    MyData data;
    char ch = '.';
    int choice;
    int pos;

    cout << "0 - вывести элементы списка\n"
        << "1 - вставить элемент в конец списка\n"
        << "2 - вставить элемент в начало списка\n"
        << "3 - вставить элемент в позицию\n"
        << "4 - удалить конечный элемент\n"
        << "5 - удалить начальный элемент\n"
        << "6 - удалить элемент с позиции\n"
        << "7 - поиск элемента по значению поля\n"
        << "8 - закончить работу\n";

    do {
        cout << "\nЧто хотите сделать? : ";
        cin >> choice;
        switch (choice)
        {
        case 0:
            if (listSize == 0) {
                cout << "Список пуст" << endl;
            }
            for (int i = 0; i < listSize; i++) {
                display(list.returnData(list.returnCurrent(i)));
            }
            break;
        case 1:
            cout << "ФИО: ";
            cin >> data.surname >> data.name >> data.lastname;
            cout << "Дата рождения(##.##.####): ";
            cin >> data.day >> ch >> data.month >> ch >> data.year;
            cout << "Адрес: ";
            cin >> data.address;

            list.pushBack(data);
            listSize++;
            break;
        case 2:
            cout << "ФИО: ";
            cin >> data.surname >> data.name >> data.lastname;
            cout << "Дата рождения(##.##.####): ";
            cin >> data.day >> ch >> data.month >> ch >> data.year;
            cout << "Адрес: ";
            cin >> data.address;

            list.pushFront(data);
            listSize++;
            break;
        case 3:
            cout << "ФИО: ";
            cin >> data.surname >> data.name >> data.lastname;
            cout << "Дата рождения(##.##.####): ";
            cin >> data.day >> ch >> data.month >> ch >> data.year;
            cout << "Адрес: ";
            cin >> data.address;

            cout << "\nВведите позицию, после которой вставится элемент: ";
            cin >> pos;
            list.insert(data, pos);
            listSize++;
            break;
        case 4:
            list.popBack();
            listSize--;
            if (listSize < 0) {
                cout << "Список пуст" << endl;
                listSize = 0;
            }
            break;
        case 5:
            list.popFront();
            listSize--;
            if (listSize < 0) {
                cout << "Список пуст" << endl;
                listSize = 0;
            }
            break;
        case 6:
            cout << "Введите позицию удаляемого элемента: ";
            cin >> pos;
            list.popFound(pos);
            listSize--;
            if (listSize < 0) {
                cout << "Список пуст" << endl;
                listSize = 0;
            }
            break;
        case 7:
            int field;
            int val;
            string str;
            cout << "Выберите поле (0,1,2,3,4,5,6): ";
            cin >> field;
            switch (field)
            {
            case 0:
                cout << "Введите день: ";
                cin >> val;

                if (list.findDay(val) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findDay(val)));
                }

                break;
            case 1:
                cout << "Введите месяц: ";
                cin >> val;

                if (list.findMonth(val) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findMonth(val)));
                }

                break;
            case 2:
                cout << "Введите год: ";
                cin >> val;

                if (list.findYear(val) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findYear(val)));
                }

                break;
            case 3:
                cout << "Введите фамилию: ";
                cin >> str;

                if (list.findSurname(str) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findSurname(str)));
                }

                break;
            case 4:
                cout << "Введите имя: ";
                cin >> str;

                if (list.findName(str) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findName(str)));
                }

                break;
            case 5:
                cout << "Введите отчество: ";
                cin >> str;

                if (list.findLastname(str) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findLastname(str)));
                }

                break;
            case 6:
                cout << "Введите адрес: ";
                cin >> str;

                if (list.findAddress(str) == NULL) {
                    cout << "Данных с таким значением поля нет" << endl;
                }
                else {
                    display(list.returnData(list.findAddress(str)));
                }

                break;
            }
            break;
        }
    } while (choice != 8);

    return 0;
}

/*
    Двусвязный список.
    Алгоритмы:
        Создание списка
        Добавление элемента в конец списка
        Добавление элемента в начало списка
        Удаление конечного элемента списка
        Удаление начального элемента списка
        Поиск элемента по заданному значению поля структуры
        Добавление элемента после найденного
        Удаление найденного элемента.
    Использовать указатели
*/