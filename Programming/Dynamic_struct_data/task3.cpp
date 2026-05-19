#include <iostream>
using namespace std;

struct list {
    int inf;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, int x) {
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t) {
        r->prev = NULL;
        h = r;
    } 
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print(list *h) {
    list *p = h;
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

// Обмен двух соседних узлов a и b (a левее b)
void swapElements(list *&h, list *&t, list *a, list *b) {
    if (a->prev) {
        a->prev->next = b;
    }
    else {
        h = b;             // a был головой, теперь голова b
    }
    if (b->next) {
        b->next->prev = a;
    }
    else {
        t = a;             // b был хвостом, теперь хвост a
    }
    b->prev = a->prev;
    a->next = b->next;
    b->next = a;
    a->prev = b;
}
void bubbleSort(list *&h, list *&t) {
    if (!h || !h->next) return;

    // Считаем длину списка
    int n = 0;
    list *p = h;
    while (p) {
        n++; 
        p = p->next;
    }

    for (int i = 0; i < n - 1; i++) {
        // Внутренний цикл: j идёт от хвоста до позиции i+1
        // Храним указатель на j-й узел — начинаем с хвоста
        list *j = t;
        int steps = n - 1 - i; // сколько шагов нужно пройти от хвоста

        for (int k = 0; k < steps; k++) {
            list *prev_j = j->prev;  // это j-1
            if (prev_j->inf > j->inf) {
                // prev_j стоит левее j — меняем их местами
                swapElements(h, t, prev_j, j);
                // после обмена: j теперь стоит левее, prev_j — правее
                // j физически сдвинулся влево, продолжаем с j->prev
            } else {
                j = j->prev; // идём левее без обмена
            }
        }
    }
}

int main() {
    int n; cout << "Введите количество элементов: "; cin >> n;
    list *head = NULL, *tail = NULL;

    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push(head, tail, x);
    }

    cout << "Исходный список: ";
    print(head);
    bubbleSort(head, tail);
    cout << "Результат:        ";
    print(head);

    return 0;
}