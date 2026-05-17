#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Сортировка вставками для одномерного массива
void insertion_sort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int j = i;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n; in >> n;
    
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> matrix[i][j];
        }
    }
    
    // Сортируем каждую диагональ, параллельную побочной
    // Диагональ определяется суммой индексов i + j = k
    // k меняется от 0 до 2n-2
    for (int k = 0; k <= 2 * n - 2; ++k) {
        vector<int> temp;

        for (int i = 0; i < n; ++i) {
            int j = k - i;
            if (j >= 0 && j < n) {
                temp.push_back(matrix[i][j]);
            }
        }
        
        insertion_sort(temp);
        int idx = 0;
        for (int i = 0; i < n; ++i) {
            int j = k - i;
            if (j >= 0 && j < n) {
                matrix[i][j] = temp[idx++];
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << matrix[i][j];
            if (j != n - 1) {
                out << ' ';
            }
        }
        out << endl;
    }
    
    return 0;
}