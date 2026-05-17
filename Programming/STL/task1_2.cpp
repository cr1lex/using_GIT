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

    // удаляем все макс эл-ты
    int mx = *max_element(v.begin(), v.end());
    auto it = remove(v.begin(), v.end(), mx);
    v.erase(it, v.end());

    // заменяем все чет эл-ты минимальным
    int mn = *min_element(v.begin(), v.end());
    replace_if(v.begin(), v.end(), [](int x) -> bool { return x % 2 == 0; }, mn);
    sort(v.begin(), v.end());

    // удаляем повтор эл-ты
    auto it = unique(v.begin(), v.end());
    v.erase(it, v.end());

    cout << "Результат:\n";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    return 0;
}
