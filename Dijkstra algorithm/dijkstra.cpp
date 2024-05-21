#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

const int mSize = 11;

class Dijkstra
{
public:
    int* dijkstra(int m[mSize][mSize], int start, int end) {
        start--;
        int size = end - start;

        int* minDist = new int[size];
        bool* visited = new bool[size];

        for (int i = 0; i < size; i++) {
            minDist[i] = INT_MAX;
            visited[i] = false;
        }
        minDist[0] = 0;

        int minIndex = -1;
        int countVisited = 0;

        for (;;) {
            int min = INT_MAX;

            for (int i = 0; i < size; i++) {
                if (!visited[i] && min >= minDist[i]) {
                    min = minDist[i];
                    minIndex = i + start;
                }
            }

            if (min != INT_MAX) {
                for (int i = 0; i < size; i++) {
                    if (m[minIndex][i + start] != 0) {
                        int tempMin = min + m[minIndex][i + start];
                        if (tempMin < minDist[i]) {
                            minDist[i] = tempMin;
                        }
                    }
                }
                visited[minIndex - start] = true;
                countVisited++;
            }

            if (countVisited == end - start) {
                break;
            }
        }

        delete[] visited;

        return minDist;
    }
};

void printDijkstra(int* minDist, int start, int end) {
    cout << "\nКратчайшие расстояния от вершины " << start << " до вершины " << end << endl;
    for (int i = 0; i < end - start + 1; i++) {
        cout << start << " - " << i + start << " = " << minDist[i] << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Dijkstra a;

    int m[mSize][mSize] = {
        {0, 4, 2, 0, 17, 14, 9, 3, 1, 0, 0},
        {4, 0, 23, 0, 7, 0, 6, 3, 8, 4, 1},
        {2, 23, 0, 11, 0, 2, 16, 6, 0, 9, 2},
        {0, 0, 11, 0, 6, 3, 8, 8, 1, 0, 14},
        {17, 7, 0, 6, 0, 14, 1, 10, 0, 7, 9},
        {14, 0, 2, 3, 14, 0, 4, 0, 1, 9, 5},
        {9, 6, 16, 8, 1, 4, 0, 11, 17, 9, 7},
        {3, 3, 6, 8, 10, 0, 11, 0, 10, 5, 14},
        {1, 8, 0, 1, 0, 1, 17, 10, 0, 4, 15},
        {0, 4, 9, 0, 7, 9, 9, 5, 4, 0, 12},
        {0, 1, 2, 14, 9, 5, 7, 14, 15, 12, 0}
    };

    //Записываем в массив m[][] данные из файла
    /*int m[mSize][mSize];

    ifstream fin("matrix.txt");
    if (fin) {
        for (int i = 0; i < mSize; i++) {
            for (int j = 0; j < mSize; j++) {
                fin >> m[i][j];
            }
        }
    }
    else {
        cout << "Не удалось открыть файл" << endl;
    }
    fin.close();*/

    cout << "Матрица " << mSize << "x" << mSize << endl << endl;
    for (int i = 0; i < mSize; i++) {
        for (int j = 0; j < mSize; j++) {
            cout << m[i][j] << "  ";
        }
        cout << endl;
    }

    int start, end;
    cout << "\nВведите начальную и конечную вершину: ";
    cin >> start >> end;

    int* minDist = a.dijkstra(m, start, end);

    printDijkstra(minDist, start, end);

    //Записываем в файл кратчайший путь до других вершин
    /*ofstream fout("matrix.txt", ios::app);
    if (fout) {
        fout << "\nКратчайшие расстояния от вершины " << start << " до вершины "  << end << endl;
        for (int i = 0; i < end - start + 1; i++) {
            fout << start << " - " << i + start << " = " << minDist[i] << endl;
        }
    }
    else {
        cout << "Не удалось открыть файл" << endl;
    }
    fout.close();*/

    delete[] minDist;

    return 0;
}