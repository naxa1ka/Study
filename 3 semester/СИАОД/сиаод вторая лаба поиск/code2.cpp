#include <iostream>
#include "cstring"
#include <ctime>
#include <algorithm>
using namespace std;

template<typename T>
static void RandomArray(T *array, int size, T &key, int seed);

template<typename T>
static T *Resize(T *oldArray, int oldSize, int newSize);

template<typename T>
static int BinarySearch(T *array, int size, T key, int &comparisons);

template<typename T>
static int LinearSearch(T *array, int size, T key, int &comparisons);

template<typename T>
static int LinearSearchWithBarrier(T *array, int size, T key, int &comparisons);

template<typename T>
static int LinearSearchOrdered(T *array, int size, T key, int &comparisons);

int main() {
    unsigned seed = unsigned(std::time(nullptr));
    int size = 200;
    int comparisons = 0;
    char key;
    char array[size];
    for (int i = 0; i < 1000; ++i) {
        RandomArray(array,size,key, seed);
        sort(array, array+size);
        BinarySearch(array, size, key, comparisons);
        //LinearSearchWithBarrier(array, size, key, comparisons);
        //cout << comparisons << endl;
    }
    cout << "Comparisons: " << comparisons << endl;
    cout << "Average number of comparisons: " << comparisons / 1000;
    return 0;
}

/**
 * Функция для увеличения размера входного массива
 * с копированием элементов.
 * @tparam T - тип массива
 * @param oldArray - предыдуший массив
 * @param oldSize - старый размер массива
 * @param newSize - новый размер массива
 * @return увеличенный массив со скопированными элементами
 */
template<typename T>
static T *Resize(T *oldArray, int oldSize, int newSize) {
    T *newArray = new T[newSize];
    memcpy(newArray, oldArray, sizeof(T) * oldSize);
    free(oldArray);
    return newArray;

}

/**
 * Линейный (последовательный) поиск.
 * \Description
 * Поиск производится путем прохождения по всему массиву и
 * сравнения на каждой итерации значения массива со значением
 * искомого ключа.
 *
 * @tparam T - тип искомого ключа и массива
 * @param array - массив с элементами, в котором производится поиск
 * @param size - размер массива
 * @param key - искомый элемент
 * @return индекс ключа массива или -1 в случае неудачи
 */
template<typename T>
static int LinearSearch(T *array, int size, T key, int &comparisons) {
    int index;
    for (index = 0; index < size; index++) {
        if (array[index] == key) break;
        comparisons += 2; //index < size;array[index] == key
    }
    return index < size ? index : -1;
}

/**
 * Линейный (последовательный) поиск с барьером.
 * \Description
 * Улучшенная версия последовательного поиска.
 * Улучшение производится путем увеличения массива на 1 справа,
 * на место пустой добавленной ячейки вставляется значение искомого ключа.
 * Таким образом мы убираем лишнее сравнение "достигнут ли конец массива",
 * что ускоряет работу алгоритма.
 *
 * @tparam T - тип искомого ключа и массива
 * @param array - массив с элементами, в котором производится поиск
 * @param size - размер массива
 * @param key - искомый элемент
 * @return индекс ключа массива или -1 в случае неудачи
 */
template<typename T>
static int LinearSearchWithBarrier(T *array, int size, T key, int &comparisons) {
    array = Resize(array, size, size + 1);
    array[size] = key;
    int index = 0;
    while (array[index] != key) {
        index++;
        comparisons++; //array[index] != key
    }
    return index < size ? index : -1;
}

/**
 * Последовательный поиск в упорядоченном массиве
 * \Description
 * Модификация последовательного поиска, но с учетом того
 * что поиск производится в упорядоченном массиве.
 * На каждой итерации проверяем, больше ли наш ключ текущего значения,
 * если больше, то идем далее, если нет, то элемент либо найден,
 * либо его нет в последовательности.
 * Также на месте size+1 элемента стоит барьер, который всегда
 * больше ключа, это обеспечивает безопасность работы с памятью
 * и убирает лишнюю проверку "достигнут ли конец массива"
 *
 * @tparam T - тип искомого ключа и массива
 * @param array - массив с элементами, в котором производится поиск
 * @param size - размер массива
 * @param key - искомый элемент
 * @return индекс ключа массива или -1 в случае неудачи
 */
template<typename T>
static int LinearSearchOrdered(T *array, int size, T key, int &comparisons) {
    array = Resize(array, size, size + 1);
    array[size] = key + 1;
    int index = 0;
    while (key > array[index]) {
        comparisons++;
        index++;
    }
    return array[index] == key ? index : -1;
}

/**
 * Бинарный поиск.
 * \Description
 * Шаг 1. Определить номер среднего элемента массива middle=(high+low)/2.
 * Шаг 2. Если значение среднего элемента массива
 * равно искомому, то возвращаем значение, равное
 * номеру искомого элемента, и алгоритм завершает работу.
 * Шаг 3. Если искомое значение больше значения среднего
 * элемента, то возьмем в качестве массива все элементы
 * справа от среднего, иначе возьмем в качестве массива
 * все элементы слева от среднего. Перейдем к Шагу 1
 *
 * @tparam T - тип искомого ключа и массива
 * @param array - массив с элементами, в котором производится поиск
 * @param size - размер массива
 * @param key - искомый элемент
 * @return индекс ключа массива или -1 в случае неудачи
 */
template<typename T>
static int BinarySearch(T *array, int size, T key, int &comparisons) {
    bool found = false;
    int high = size - 1;
    int low = 0;
    int middle = (high + low) / 2;
    while (!found && high >= low) {
        comparisons += 2; //!found; high>=low;
        if (key == array[middle]) {
            found = true;
            comparisons++;
        } else if (key < array[middle]) {
            high = middle - 1;
            comparisons++;
        } else {
            low = middle + 1;
            comparisons++;
        }
        middle = (high + low) / 2;
    }
    return found ? middle : -1;
}

template<typename T>
static void RandomArray(T *array, int size, T &key, int seed) {
    srand(seed+key); //рекурсивно сбрасываем сид для генерации
                     //начальный сид - время
    for (int i = 0; i < size; ++i) {
        array[i] = 48 + rand() % 75;
        //48 - пропускаем спец символы
        //rand [0;74]; 48 - 122
    }
    key = rand() % 123;
}