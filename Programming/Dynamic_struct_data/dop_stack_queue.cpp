#include <iostream>
#include <string>
using namespace std;

struct stack {
    int inf;
    stack *next;
};

void push(stack *(&h), int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack *(&h)) {
    int i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}

int main() {
    cout << "Введите выражение в постфиксной форме (однозначные числа, без пробелов):" << endl;
    cout << "Пример: 3482/+*2-" << endl;
    string str; cin >> str;
    
    stack *res = NULL;   
    for (int i = 0; i < (int)str.size(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            push(res, c - '0');
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // Знак операции: извлекаем два операнда
            // Стек хранит в обратном порядке: первым извлекается b, потом a
            // Выражение было "... a b op", значит вычисляем a op b
            int b = pop(res);
            int a = pop(res);
            int result = 0;
            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        cout << "Ошибка: деление на ноль!" << endl;
                        return 0;
                    }
                    result = a / b;
                    break;
            }
            push(res, result);
        }
        // Остальные символы (пробелы и т.д.) пропускаем
    }
    cout << "Результат: " << pop(res) << endl;
    return 0;
}
