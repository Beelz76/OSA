#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
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

    bool isEmpty;
};

class Database
{
private:
    MyData* data;
    int databaseSize;
    char* databaseName;

public:
    Database(string dbName, int size) {
        databaseName = new char[dbName.size() + 1];
        strcpy_s(databaseName, dbName.size() + 1, dbName.c_str());

        data = new MyData[size];
        databaseSize = size;

        for (int i = 0; i < databaseSize; i++) {
            data[i].isEmpty = true;
        }
    }

    ~Database() {
        delete[] data;
    }

    //Очистка структурных переменных (отметка переменной как не содержащей данных). Функция должна получать в качестве параметра индекс массива.
    void deleteData(int index) {
        data[index].isEmpty = true;
    }

    //Поиск свободной структурной переменной. Функция должна возвращать индекс первого свободного элемента в массиве структур.
    int findEmpty() {
        for (int i = 0; i < databaseSize; i++) {
            if (data[i].isEmpty) {
                return i;
            }
        }

        return -1;
    }

    //Ввод элементов (полей) структуры с клавиатуры. В качестве параметра в функцию должен передаваться индекс элемента массива.
    void addData(int index, MyData newData) {
        data[index] = newData;
        data[index].isEmpty = false;
    }

    //Вывод элементов (полей) структуры на монитор. В функцию должен передаваться индекс элемента массива.
    MyData* print(int index) {
        if (data[index].isEmpty == true) {
            return (MyData*)NULL;
        }

        return &data[index];
    }

    //Поиск в массиве структур элемента с заданным значением поля или с наиболее близким к нему по значению. Предусмотреть возможность задания одного числового значения и одного строкового.
    MyData* findNearestDay(int day) {
        int index = -1;
        int minDiff = INT_MAX;

        for (int i = 0; i < databaseSize; i++) {
            if (!data[i].isEmpty) {
                int valueDiff = abs(data[i].day - day);

                if (valueDiff < minDiff) {
                    minDiff = valueDiff;
                    index = i;
                }
            }
        }

        if (index == -1) {
            return (MyData*)NULL;
        }
        else {
            return &data[index];
        }
    }

    MyData* findNearestMonth(int month) {
        int index = -1;
        int minDiff = INT_MAX;

        for (int i = 0; i < databaseSize; i++) {
            if (!data[i].isEmpty) {
                int valueDiff = abs(data[i].month - month);

                if (valueDiff < minDiff) {
                    minDiff = valueDiff;
                    index = i;
                }
            }
        }

        if (index == -1) {
            return (MyData*)NULL;
        }
        else {
            return &data[index];
        }
    }

    MyData* findNearestYear(int year) {
        int index = -1;
        int minDiff = INT_MAX;

        for (int i = 0; i < databaseSize; i++) {
            if (!data[i].isEmpty) {
                int valueDiff = abs(data[i].year - year);

                if (valueDiff < minDiff) {
                    minDiff = valueDiff;
                    index = i;
                }
            }
        }

        if (index == -1) {
            return (MyData*)NULL;
        }
        else {
            return &data[index];
        }
    }

    MyData* findNearestName(string name) {
        for (int i = 0; i < databaseSize; i++) {
            if (data[i].isEmpty) {
                continue;
            }

            if (string(data[i].name).find(name) != string::npos) {
                return &data[i];
            }

            return NULL;
        }
    }

    MyData* findNearestSurname(string surname) {
        for (int i = 0; i < databaseSize; i++) {
            if (data[i].isEmpty) {
                continue;
            }

            if (string(data[i].surname).find(surname) != string::npos) {
                return &data[i];
            }

            return NULL;
        }
    }

    MyData* findNearestLastname(string lastname) {
        for (int i = 0; i < databaseSize; i++) {
            if (data[i].isEmpty) {
                continue;
            }

            if (string(data[i].lastname).find(lastname) != string::npos) {
                return &data[i];
            }

            return NULL;
        }
    }

    MyData* findNearestAddress(string address) {
        for (int i = 0; i < databaseSize; i++) {
            if (data[i].isEmpty) {
                continue;
            }

            if (string(data[i].address).find(address) != string::npos) {
                return &data[i];
            }

            return NULL;
        }
    }

    //Поиск в массиве структуры с минимальным значением заданного поля. Поле должно передаваться в поле числом, обозначающим номер поля в структуре.
    MyData* findMin(bool (*field)(MyData, MyData)) {
        int index = 0;
        MyData min = data[0];

        for (int i = 0; i < databaseSize; i++) {
            if (data[i].isEmpty) {
                continue;
            }

            if (field(min, data[i])) {
                min = data[i];
                index = i;
            }
        }

        return &data[index];
    }

    //Сортировка массива структур в порядке возрастания заданного поля (при сортировке можно использовать тот факт, что в С++ разрешается присваивание структурированных переменных);
    void sortBy(bool (*upndown)(MyData, MyData)) {
        for (int i = 0; i < databaseSize - 1; i++) {
            for (int j = 0; j < databaseSize - i - 1; j++) {
                if (upndown(data[j], data[j + 1])) {
                    swap(&data[j], &data[j + 1]);
                }
            }
        }
    }

    //Функция чтения файла с содержимым базы данных(массива структурных элементов).
    void restoreData() {
        FILE* file;

        fopen_s(&file, databaseName, "rb");

        for (int i = 0; i < databaseSize; i++) {
            fread(&data[i], sizeof(MyData), 1, file);
        }

        fclose(file);
    }

    //Функция записи в файл содержимого базы данных(массива структурных элементов).
    void saveData() {
        FILE* file;

        fopen_s(&file, databaseName, "wb");

        for (int i = 0; i < databaseSize; i++) {
            fwrite(&data[i], sizeof(MyData), 1, file);
        }

        fclose(file);
    }

    void cleanUp() {
        for (int i = 0; i < databaseSize; i++) {
            data[i].isEmpty = true;
        }

        databaseSize = 0;
    }

    void swap(MyData*, MyData*);
};

void Database::swap(MyData* a, MyData* b) {
    MyData temp = *a;
    *a = *b;
    *b = temp;
}

void output(MyData a) {
    cout << a.surname << " " << a.name << " " << a.lastname << "  " << a.day
        << '.' << a.month << '.' << a.year << '\n' << a.address << endl << endl;
}

void output(MyData* a) {
    cout << a->surname << " " << a->name << " " << a->lastname << "  " << a->day
        << '.' << a->month << '.' << a->year << '\n' << a->address << endl << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    int dbSize = 2;
    string dbName = "LAB2.bin";

    Database* database = new Database(dbName, dbSize);

    //Добавление данных
    for (int i = 0; i < dbSize; i++) {
        char ch = '.';
        MyData data;
        cout << "ФИО: ";
        cin >> data.surname >> data.name >> data.lastname;
        cout << "Дата рождения(##.##.####): ";
        cin >> data.day >> ch >> data.month >> ch >> data.year;
        cout << "Адрес: ";
        cin >> data.address;

        database->addData(i, data);

        cout << "Данные " << i + 1 << " добавлены" << endl << endl;
    }

    //Сохранение данных
    database->saveData();

    //Удаление и восстановление данных
    delete database;
    database = new Database(dbName, dbSize);
    database->restoreData();

    //Вывод всех данных на экран
    for (int i = 0; i < dbSize; i++) {
        MyData* a = database->print(i);
        output(a);
    }

    //Поиск ближайшего
    int nearestInt;
    string nearestString;
    MyData* nrstString;
    MyData* nrstData;
    int field;
    cout << "\nВведите номер поля (поиск ближайшего): ";
    cin >> field;
    switch (field)
    {
    case 1:
        cout << "Введите строку: ";
        cin >> nearestString;
        nrstString = database->findNearestSurname(nearestString);
        if (nrstString == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по фамилии" << endl;
            output(nrstString);
        }
        break;
    case 2:
        cout << "Введите строку: ";
        cin >> nearestString;
        nrstString = database->findNearestName(nearestString);
        if (nrstString == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по имени" << endl;
            output(nrstString);
        }
        break;
    case 3:
        cout << "Введите строку: ";
        cin >> nearestString;
        nrstString = database->findNearestLastname(nearestString);
        if (nrstString == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по отчеству" << endl;
            output(nrstString);
        }
        break;
    case 4:
        cout << "Введите число: ";
        cin >> nearestInt;
        nrstData = database->findNearestDay(nearestInt);
        if (nrstData == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по дню рождения" << endl;
            output(nrstData);
        }
        break;
    case 5:
        cout << "Введите число: ";
        cin >> nearestInt;
        nrstData = database->findNearestMonth(nearestInt);
        if (nrstData == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по месяцу рождения" << endl;
            output(nrstData);
        }
        break;
    case 6:
        cout << "Введите число: ";
        cin >> nearestInt;
        nrstData = database->findNearestYear(nearestInt);
        if (nrstData == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по году рождения" << endl;
            output(nrstData);
        }
        break;
    case 7:
        cout << "Введите строку: ";
        cin >> nearestString;
        nrstString = database->findNearestAddress(nearestString);
        if (nrstString == NULL) {
            cout << "Ошибка!" << endl;
        }
        else {
            cout << "Ближайшее по адресу" << endl;
            output(nrstString);
        }
        break;
    }

    //Поиск минимального
    int number;
    cout << "\nВведите номер поля (поиск минимального): ";
    cin >> number;
    MyData* smData;
    switch (number)
    {
    case 1:
        cout << "Min по фамилии" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return string(d1.surname) > string(d2.surname); });
        output(smData);
        break;
    case 2:
        cout << "Min по имени" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return string(d1.name) > string(d2.name); });
        output(smData);
        break;
    case 3:
        cout << "Min по отчеству" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return string(d1.lastname) > string(d2.lastname); });
        output(smData);
        break;
    case 4:
        cout << "Min по дню рождения" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return d1.day > d2.day; });
        output(smData);
        break;
    case 5:
        cout << "Min по месяцу рождения" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return d1.month > d2.month; });
        output(smData);
        break;
    case 6:
        cout << "Min по году рождения" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return d1.year > d2.year; });
        output(smData);
        break;
    case 7:
        cout << "Min по адресу" << endl;
        smData = database->findMin([](MyData d1, MyData d2) { return string(d1.address) > string(d2.address); });
        output(smData);
        break;
    }

    //Сортировки
    cout << "\nСортировка по году рождения (по возрастанию)" << endl;
    database->sortBy([](MyData d1, MyData d2) { return d1.year > d2.year; });
    for (int i = 0; i < dbSize; i++) {
        MyData* a = database->print(i);
        output(a);
    }

    cout << "\nСортировка по имени (по убыванию)" << endl;
    database->sortBy([](MyData d1, MyData d2) { return string(d1.name) < string(d2.name); });
    for (int i = 0; i < dbSize; i++) {
        MyData* a = database->print(i);
        output(a);
    }

    cout << "! Очистка базы данных !\n" << "-----------------------\n";
    database->cleanUp();
    cout << "Очистка завершена\n";

    return 0;
}

/*
    Разработать функции в соответствии с ниже приводимым перечнем:
    1.  Очистка структурных переменных (отметка переменной как не содержащей данных). Функция должна получать в качестве параметра индекс массива.
    2.  Поиск свободной структурной переменной. Функция должна возвращать индекс первого свободного элемента в массиве структур.
    3.  Ввод элементов (полей) структуры с клавиатуры. В качестве параметра в функцию должен передаваться индекс элемента массива.
    4.  Вывод элементов (полей) структуры на монитор. В функцию должен передаваться индекс элемента массива.
    5.  Вывод на экран всех заполненных элементов массива структур.
    6.  Поиск в массиве структур элемента с заданным значением поля или с наиболее близким к нему по значению. Предусмотреть возможность задания одного числового значения и одного строкового.
    7.  Поиск в массиве структуры с минимальным значением заданного поля. Поле должно передаваться в поле числом, обозначающим номер поля в структуре.
    8.  Сортировка массива структур в порядке возрастания заданного поля (при сортировке можно использовать тот факт, что в С++ разрешается присваивание структурированных переменных);
    9.  Сортировка массива структур в порядке убывания заданного поля (при сортировке можно использовать тот факт, что в С++ разрешается присваивание структурированных переменных);
    10. Функция чтения файла с содержимым базы данных (массива структурных элементов).
    11. Функция записи в файл содержимого базы данных (массива структурных элементов).
*/