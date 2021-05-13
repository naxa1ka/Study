#include <iostream>
#include <fstream>
#include "windows.h"
#include <ctime>
#include <cmath>
#include <iomanip>

#define PI 3.14159265
using namespace std;

template<typename T>
static void RecordingFile(const string &filename, T *array, int size, DWORD timeWork);

template<typename T>
static void JustRandom(T *array, int size);

template<typename T>
static void Growing(T *array, int size, int beginRange, int endRange);

template<typename T>
static void Decreasing(T *array, int size, int beginRange, int endRange);

template<typename T>
static void Sawtooth(T *array, int size, int beginRange, int endRange, int interval);

template<typename T>
static void StairStepped(T *array, int size, int beginRange, int endRange, int interval);

//only double
static void QuasiOrdered(double *array, int size, int beginRange, int endRange, int interval);

//only double
static void Sinusoidal(double *array, int size, int beginRange, int endRange, int interval);

int main() {
    string filename_1 = "..\\files\\test.txt";
    setlocale(LC_ALL, "Russian");
    int size = 10000;
    double *array = new double[size];
    srand(time(0));
    DWORD timeStart = GetTickCount();
    //JustRandom(array, size);
   // Growing(array, size, 0, 20000);
    //Decreasing(array, size, 10000, 0);
    //Sinusoidal(array, size, 0, 20000, 2000);
    StairStepped(array, size, 0, 20000, 2000);
    //Sawtooth(array, size, 20000, 0, 2000);

    //QuasiOrdered(array, size, 0, 20000, 2000);
    DWORD timeEnd = GetTickCount();
    DWORD timeWork = timeEnd - timeStart;
    cout << "Время: " << timeWork << " миллисекунд";
    RecordingFile(filename_1, array, size, timeWork);
    return 0;//одна
}

template<typename T>
static void JustRandom(T *array, int size) {
    array[0] = rand();
    for (int i = 1; i < size; ++i) {
        array[i] = rand() % (int) array[i - 1] + rand();
    }
}

template<typename T>
static void Growing(T *array, int size, int beginRange, int endRange) {
    T step = (endRange - beginRange) / size;
    int growingStep = beginRange + step;
    array[0] = beginRange;
    for (int i = 1; i < size - 1; ++i) {
        array[i] = growingStep + rand() % (int) step;
        growingStep += step;
    }
    array[size - 1] = endRange;
}

template<typename T>
static void Decreasing(T *array, int size, int beginRange, int endRange) {
    T step = (beginRange - endRange) / size;
    int decreasingStep = beginRange - step;

    array[0] = beginRange;
    for (int i = 1; i < size - 1; ++i) {
        array[i] = decreasingStep - rand() % (int) step;
        decreasingStep -= step;
    }
    array[size - 1] = endRange;
}

//only double
static void Sinusoidal(double *array, int size, int beginRange, int endRange, int interval) {
    double sinStep = 360.0 / interval;
    int step = (endRange - beginRange) / 2;
    int stepRandom = (endRange - beginRange) / size;
    double j = 90.0;

    for (int i = 0; i < size; ++i) {
        array[i] = step + sin(j * PI / 180) * step - rand() % stepRandom;
        j += sinStep;
    }
}

template<typename T>
static void StairStepped(T *array, int size, int beginRange, int endRange, int interval) {
    int countInterval = size / interval;
    int sizeRandomInterval = (endRange - beginRange) / countInterval;
    for (int j = 0, shift = 0; j < countInterval; ++j,
            shift += interval) {  //сдвиг вправо для создания нескольких интервалов {
        for (int i = shift; i < interval + shift; ++i) {
            array[i] = sizeRandomInterval * j + rand() % sizeRandomInterval;
        }
    }
}

template<typename T>
static void Sawtooth(T *array, int size, int beginRange, int endRange, int interval) {
    double fallRatio = 0.8;
    int countInterval = size / interval;

    int fallStep = (beginRange - endRange) / interval;
    int upStep = (fallRatio / (1 - fallRatio)) * (beginRange - endRange) / interval;

    for (int j = 0, shift = 0; j <= countInterval; ++j, shift += interval) {
        int decreasingStep = beginRange - fallStep;

        for (int i = shift; i < interval * fallRatio + shift; ++i) {
            array[i] = decreasingStep - rand() % fallStep;
            decreasingStep -= fallStep;
        }

        int growBeginRange = array[(int) (interval * fallRatio)];
        int growingStep = growBeginRange + upStep;

        for (int i = interval * fallRatio + shift; i < interval + shift; ++i) {
            array[i] = growingStep + rand() % upStep;
            growingStep += upStep;
        }
    }
}

//only double
static void QuasiOrdered(double *array, int size, int beginRange, int endRange, int interval) {
    bool isGrow = true;
    int countGrowInterval = size / 100;
    double sinStep = 360.0 / interval;
    int step = (endRange - beginRange) / interval;
    double s = 90.0;
    array[0] = beginRange;
    for (int j = 1, shift = 0; j <= countGrowInterval; ++j, shift += size / countGrowInterval) {
        for (int i = shift; i < size / countGrowInterval + shift; ++i) {
            if (i == 0) continue;
            if (isGrow == 1) {
                array[i] = array[i - 1] + (rand() % step) * sin(s * PI / 180);
            } else {
                array[i] = array[i - 1] - (rand() % step) * sin(s * PI / 180);
            }
            s += sinStep;
        }
        isGrow = rand() % 2;
    }
}

template<typename T>
static void RecordingFile(const string &filename, T *array, int size, DWORD timeWork) {
    ofstream fileout(filename);
    fileout << "Operating time (ms): " << timeWork << endl;
    fileout << "Array size: " << size << endl;
    for (int i = 0; i < size; ++i) {
        fileout << array[i] << endl;
    }
    fileout.close();
}

