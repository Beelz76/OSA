#include <iostream>
using namespace std;

class Queue
{
private:
    int* arr;
    int head;
    int tail;
    int N = 10;

public:
    class Full {};
    class Empty {};

    Queue() {
        head = 0;
        tail = 0;
        arr = new int[N];
    }

    Queue(int m) {
        N = m + 1;
        head = 0;
        tail = 0;
        arr = new int[m];
    }

    ~Queue() {
        delete[] arr;
    }

    void add_item(int a) {
        if (head == (tail + 1) % N) {
            throw Full();
        }
        else {
            arr[tail] = a;
            tail = (tail + 1) % N;
        }
    }

    int extract_item() {
        int val;
        if (head != tail) {
            val = arr[head];
            head = (head + 1) % N;
            return val;

        }
        else
        {
            throw Empty();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int num;
    bool r;
    int size;

    cout << "Размер очереди: ";
    cin >> size;

    Queue one(size);
    do {
        cout << "Для добавления введите 1, для извлечения 0: ";
        cin >> r;
        if (r) {
            cout << "Введите значение: ";
            cin >> num;
            try
            {
                one.add_item(num);
            }
            catch (Queue::Full)
            {
                cout << "Очередь заполнена!" << endl;
            }
        }
        else {
            cout << "Значение равно: ";
            try
            {
                cout << one.extract_item() << endl;
            }
            catch (Queue::Empty)
            {
                cout << "Очередь пуста!" << endl;
            }
        }
    } while (true);

    return 0;
}

/*
    Очередь.

    Необходимо разработать программу, реализующую работу с очередью.

    Программа должна содержать функции:
        вставки
        извлечения

    Необходимо предусмотреть:
        контроль на переполнение
        контроль на отсутствие элементов
        отображение на экране значения извлекаемого элемента
*/