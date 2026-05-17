#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// просеивание элемента вниз в куче
void heapify(vector<int> &arr, int n, int i) {
    int max = i;          // считаем родителя наибольшим
    int left = 2 * i + 1;     
    int right = 2 * i + 2;    
    bool not_max = false;

    if (left < n && arr[left] > arr[max])
        max = left;
        not_max = true;
    
    if (right < n && arr[right] > arr[max])
        max = right;
        not_max = true;
    
    if (not_max) {
        swap(arr[i], arr[max]);
        heapify(arr, n, max);
    }
}

void heapSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    // извлекаем элементы из кучи по одному
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);   
        heapify(arr, i, 0);    
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N; in >> N;
    vector<vector<int>> matrix(N, vector<int>(N));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            in >> matrix[i][j];

    // Сортируем каждый столбец
    for (int j = 0; j < N; ++j) {
        vector<int> column(N);
        for (int i = 0; i < N; ++i)
            column[i] = matrix[i][j];
        heapSort(column);
        for (int i = 0; i < N; ++i)
            matrix[i][j] = column[i];
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            out << matrix[i][j] << " ";
        out << endl;
    }

    return 0;
}