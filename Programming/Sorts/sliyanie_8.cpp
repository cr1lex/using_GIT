#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// добавить параметр bool reverse_sort
void conc_of_two_arr(vector<int> &arr, int l, int r, int m, bool reverse) {
    if (l >= r || m < l || m > r) { return; }
    if (r - l + 1 == 2) {
        if ((!reverse && arr[l] > arr[r]) || (reverse && arr[l] < arr[r])) {
            swap(arr[l], arr[r]);
        }
        return; 
    }
    vector<int> buf(r - l + 1);
    int cur = 0;
    int i = l; int j = m + 1;
    while (r - l + 1 != cur) {
        if (i > m) {
            for (int k = j; k <= r; ++k) {
                buf[cur] = arr[k];
                ++cur;
            }
        }
        else if (j > r) {
            for (int k = i; k <= m; ++k) {
                buf[cur] = arr[k];
                ++cur;
            }
        }
        else if (!reverse) {
            if (arr[i] > arr[j]) {
                buf[cur] = arr[j];
                ++j;
                ++cur;
            }
            else {
                buf[cur] = arr[i];
                ++i;
                ++cur;
            }
        }
        else {
            if (arr[i] > arr[j]) {
                buf[cur] = arr[i];
                ++i;
                ++cur;
            }
            else {
                buf[cur] = arr[j];
                ++j;
                ++cur;
            }
        }
        
        
    }
    int ind = 0;
    while (l != r+1) {
        arr[l] = buf[ind];
        ++ind;
        ++l;
    }

}

void sort_sliyanie(vector<int> &arr, int l, int r, bool reverse) {
    if (l >= r) { return; }
    int m = (l + r) / 2;
    sort_sliyanie(arr, l, m, reverse);
    sort_sliyanie(arr, m + 1, r, reverse);
    conc_of_two_arr(arr, l, r, m, reverse);
}


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N; in >> N;
    // N эл-тов vector<int>(N)
    vector<vector<int>> matrix(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            in >> matrix[i][j];
        }
    }

    for (int j = 0; j < N; ++j) {
        bool reverse = false;
        if ((j + 1) % 3 == 0) {
            reverse = true;
        }
        sort_sliyanie(matrix[j], 0, N - 1, reverse);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            out << matrix[i][j];
            if (j != N - 1) {
                out << ' ';
            }
        }
        out << endl;
    }
    
    return 0;
}