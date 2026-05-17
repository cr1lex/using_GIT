#include <iostream>
#include <vector>
#include <numeric>
#include <functional>

using namespace std;

int main() {
    int n; cout << "Введите n: "; cin >> n; cout << endl;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {cin >> a[i];}
    for (int i = 0; i < n; ++i) {cin >> b[i];}

    int count = inner_product(
        a.begin(), a.end(),
        b.begin(),
        0,
        plus<int>(),              // из <functional>
        equal_to<int>()           // из <functional>
    );

    cout << count;
    return 0;
}