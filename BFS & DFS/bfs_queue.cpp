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

class Queue
{
private:
    Node* head;
    Node* tail;

public:
    Queue() {
        head = tail = nullptr;
    }

    ~Queue() {
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

    void pop_front() {
        Node* delNode = head;

        if (delNode == tail) {
            tail = head = nullptr;
            delete delNode;
            return;
        }

        head = head->next;
        head->prev = nullptr;

        delete delNode;
    }

    bool isEmpty() {
        if (head == nullptr) {
            return true;
        }

        return false;
    }

    int getFirst() {
        return head->data;
    }
};

class AlgorithmBFS
{
public:
    vector<int> BFS(int m[mSize][mSize], int start, int end) {
        start--, end--;
        Queue q;
        bool visited[mSize];
        int ways[mSize];
        int dist[mSize];

        for (int i = 0; i < mSize; i++) {
            visited[i] = false;
            dist[i] = NULL;
        }
        visited[start] = true;

        q.push_back(start);
        ways[start] = -1;
        dist[start] = 0;

        while (!q.isEmpty()) {
            int unit = q.getFirst();
            q.pop_front();
            for (int i = 0; i < mSize; i++) {
                if (!visited[i] && m[unit][i] == 1) {
                    q.push_back(i);
                    ways[i] = unit;
                    dist[i] = dist[unit] + 1;
                    visited[i] = true;
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

    AlgorithmBFS a;
    int start, end;
    char ch;

    do {
        cout << "\nВведите начальную и конечную вершину: ";
        cin >> start >> end;

        vector<int> vec = a.BFS(m, start, end);

        cout << "\nПуть: ";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] + 1 << " ";
        }

        cout << "\nПродолжить (y/n)?: ";
        cin >> ch;
    } while (ch != 'n');

    return 0;
}