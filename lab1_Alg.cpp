#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <algorithm> 
#include <random>    

using namespace std;

class HashTable {
private:
    vector<int> table;  // массив для хеш-таблицы
    int size;           // число ячеек
    int numberOfSteps;  // счётчик проб

public:
    HashTable(int s) {
        size = s;
        table.assign(size, -1);
        numberOfSteps = 0;
    }

    // Хеш-функция: сумма всех цифр ключа
    int hashFunction(int key) {
        int sum = 0, temp = key;
        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }
        return sum % size;
    }

    // Вставка с квадратичным пробированием
    void insert(int key) {
        int hash = hashFunction(key);
        int i = 0;
        int newIndex = hash;

        while (table[newIndex] != -1) {
            numberOfSteps++;
            i++;
            newIndex = (hash + i * i) % size;
            if (i >= size) {
                cout << "Ошибка: таблица переполнена!\n";
                return;
            }
        }

        table[newIndex] = key;
        numberOfSteps++;
    }

    // Вывод таблицы 
    void display() {
        const int columns = 11;
        cout << endl;
        for (int i = 0; i < size; i += columns) {

            for (int j = i; j < i + columns && j < size; j++) {
                cout << setw(8) << j;
            }
            cout << endl;
            for (int j = i; j < i + columns && j < size; j++) {
                if (table[j] == -1)
                    cout << setw(8) << " ";
                else
                    cout << setw(8) << table[j];
            }
            cout << endl << endl;
        }
    }

    // Анализ таблицы
    void analyze(int totalKeys) {
        int filled = 0;
        for (int i = 0; i < size; i++) {
            if (table[i] != -1)
                filled++;
        }

        double fillFactor = (double)filled / size;
        double averageSteps = (double)numberOfSteps / totalKeys;

        cout << "Количество элементов: " << totalKeys << endl;
        cout << "Размер таблицы: " << size << endl;
        cout << "Коэффициент заполнения таблицы: "<< fixed << setprecision(6) << fillFactor << endl;
        cout << "Среднее число шагов: "<< fixed << setprecision(5) << averageSteps << endl;
    }
};

// Генерация уникальных четырёхзначных неотсортированных чисел
vector<int> generateUniqueNumbers(int count) {
    set<int> uniqueNumbers;
    srand(time(0));

    while ((int)uniqueNumbers.size() < count) {
        int num = 1000 + rand() % 9000;
        uniqueNumbers.insert(num);
    }
    vector<int> numbers(uniqueNumbers.begin(), uniqueNumbers.end());

    random_device rd;
    mt19937 g(rd());
    shuffle(numbers.begin(), numbers.end(), g);

    return numbers;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int m = 55; // количество элементов
    int t = static_cast<int>(1.5 * m);

    HashTable ht(t);

    vector<int> numbers = generateUniqueNumbers(m);

    cout << "\nСгенерированная последовательность:\n";
    int count = 0;
    for (int num : numbers) {
        cout << num << " ";
        ht.insert(num);
        count++;
        if (count % 10 == 0)
            cout << endl;
    }
    cout << endl;

    ht.display();
    ht.analyze(m);

    return 0;
}
