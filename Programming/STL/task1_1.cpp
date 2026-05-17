#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n; cout << "Количество элементов: "; cin >> n;

    vector<int> v(n);
    cout << "Введите элементы:\n";
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    int mn = *min_element(v.begin(), v.end());
    replace_if(v.begin(), v.end(), [](int x) -> bool { return x % 2 == 0; }, mn);

    cout << "Результат:\n";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
   
    return 0;
}
