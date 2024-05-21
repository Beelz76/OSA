#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int mSize = 11;

class AlgorithmDFS
{
private:
    bool visited[mSize];
    int ways[mSize];
    vector<int> result;

public:
    void preDFS(int start, int end) {
        for (int i = 0; i < mSize; i++) {
            visited[i] = false;
        }

        ways[start] = -1;
    }

    void DFS(int m[mSize][mSize], int start) {
        visited[start] = true;

        for (int i = 0; i < mSize; i++) {
            if (!visited[i] && m[start][i] == 1) {
                ways[i] = start;
                DFS(m, i);
            }
        }
    }

    vector <int> toVec(int start, int end) {
        result.clear();

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

        a.preDFS(start - 1, end - 1);
        a.DFS(m, start - 1);

        vector <int> vec = a.toVec(start - 1, end - 1);

        cout << "\nПуть: ";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] + 1 << " ";
        }

        cout << "\nПродолжить (y/n)?: ";
        cin >> ch;
    } while (ch != 'n');

    return 0;
}