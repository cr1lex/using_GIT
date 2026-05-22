#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int get_digit(int num, int pos, int total_digits) {
    int shifted = num / (int)pow(10, total_digits - 1 - pos);
    return shifted % 10;
}

int count_digits(int num) {
    if (num == 0) {return 1;}
    int cnt = 0;
    while (num > 0) {
        ++cnt;
        num /= 10;
    }
    return cnt;
}

void msd_helper(vector<int>& arr, int digit_pos, int total_digits) {
    if (arr.size() <= 1 || digit_pos >= total_digits) {return;}
    vector<int> buckets[10];
    for (int i = 0; i < arr.size(); ++i) {
        int d = get_digit(arr[i], digit_pos, total_digits);
        buckets[d].push_back(arr[i]);
    }

    cout << "Разряд " << (total_digits - digit_pos) << " (позиция " << digit_pos << "):" << endl;
    for (int d = 0; d <= 9; ++d) {
        if (!buckets[d].empty()) {
            cout << "  Корзина [" << d << "]: ";
            for (int i = 0; i < buckets[d].size(); ++i) {
                cout << buckets[d][i] << " ";
            }
            cout << endl;
        }
    }

    for (int d = 0; d <= 9; ++d) {
        if (buckets[d].size() > 1) {
            msd_helper(buckets[d], digit_pos + 1, total_digits);
        }
    }
    int idx = 0;
    for (int d = 0; d <= 9; ++d) {
        for (int i = 0; i < buckets[d].size(); ++i) {
            arr[idx] = buckets[d][i];
            ++idx;
        }
    }
    cout << "После объединения корзин: ";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void msd_sort(vector<int>& arr) {
    if (arr.empty()) {return;}
    int max_val = arr[0];
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    int total_digits = count_digits(max_val);
    cout << "Максимальное число: " << max_val
         << ", разрядов: " << total_digits << endl << endl;
    msd_helper(arr, 0, total_digits);
}

int main() {
    cout << "Введите количество чисел: ";
    int n; cin >> n;
    vector<int> arr(n);
    cout << "Введите числа: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << "\nИсходный массив: ";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;
    
    cout << "=== MSD поразрядная сортировка ===" << endl << endl;
    msd_sort(arr);
    cout << "\nОтсортированный массив: ";
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}