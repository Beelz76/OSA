#include <iostream>
using namespace std;

class Stack
{
private:
    int* arr;
    int top;
    int N = 10;

public:
    class Full {};
    class Empty {};

    Stack() {
        top = -1;
        arr = new int[N];
    }

    Stack(int m) {
        N = m;
        top = -1;
        arr = new int[m];
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int a) {
        if (top == N - 1) {
            throw Full();
        }
        else {
            arr[++top] = a;
        }
    }

    int pop() {
        if (top >= 0) {
            return arr[top--];
        }
        else {
            throw Empty();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int num;
    bool r;
    int size;

    cout << "Размер стека: ";
    cin >> size;

    Stack st(size);
    do {
        cout << "Для push введите 1, для pop 0: ";
        cin >> r;
        if (r) {
            cout << "Введите значение: ";
            cin >> num;
            try
            {
                st.push(num);
            }
            catch (Stack::Full)
            {
                cout << "Стек переполнен!" << endl;
            }
        }
        else {
            cout << "Значение равно: ";
            try
            {
                cout << st.pop();
            }
            catch (Stack::Empty)
            {
                cout << "Стек пуст!" << endl;
            }
        }
    } while (true);

    return 0;
}

/*
    Стек

    Необходимо разработать программу, реализующую работу со стеком.

    Программа должна содержать функции:
        вставки
        извлечения

    Необходимо предусмотреть:
        контроль на переполнение
        контроль на отсутствие элементов
        отображение на экране значения извлекаемого элемента
*/
