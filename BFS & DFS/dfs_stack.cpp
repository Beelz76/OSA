#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int mSize = 11;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node() {
        next = prev = nullptr;
    }
};

class Stack
{
private:
    Node* head;
    Node* tail;

public:
    Stack() {
        head = tail = nullptr;
    }

    ~Stack() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void push_back(int d) {
        Node* newNode = new Node;

        newNode->data = d;

        if (head == nullptr) {
            head = tail = newNode;
            newNode->prev = nullptr;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop_back() {
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

    bool isEmpty() {
        if (head == nullptr) {
            return true;
        }

        return false;
    }

    int getTop() {
        return tail->data;
    }
};

class AlgorithmDFS
{
public:
    vector<int> DFS(int m[mSize][mSize], int start, int end) {
        start--, end--;
        Stack st;
        bool visited[mSize];
        int ways[mSize];

        for (int i = 0; i < mSize; i++) {
            visited[i] = false;
        }
        visited[start] = true;

        st.push_back(start);
        ways[start] = -1;

        while (!st.isEmpty()) {
            int unit = st.getTop();
            visited[unit] = true;

            st.pop_back();


            for (int i = 0; i < mSize; i++) {
                if (!visited[i] && m[unit][i] == 1) {
                    st.push_back(i);
                    ways[i] = unit;
                }
            }
        }

        vector<int> result;
        result.push_back(end);

        do {
            result.push_back(ways[end]);
            end = ways[end];
        } while (end != start);

        reverse(result.begin(), result.end());

        return result;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int m[mSize][mSize] = {
        {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1},
        {1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0},
        {1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0}
    };

    cout << "Матрица смежности " << mSize << "x" << mSize << endl << endl;
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            cout << m[i][j] << "  ";
        }
        cout << endl;
    }

    AlgorithmDFS a;
    int start, end;
    char ch;

    do {
        cout << "\nВведите начальную и конечную вершину: ";
        cin >> start >> end;

        vector<int> vec = a.DFS(m, start, end);

        cout << "\nПуть: ";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] + 1 << " ";
        }

        cout << "\nПродолжить (y/n)?: ";
        cin >> ch;
    } while (ch != 'n');

    return 0;
}