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

int findMax(list *h) {
    int maxVal = h->inf;
    list *p = h->next;
    while (p) {
        if (p->inf > maxVal)
            maxVal = p->inf;
        p = p->next;
    }
    return maxVal;
}

// вставить после узла r
void insertAfter(list *&h, list *&t, list *r, int y) {
    list *p = new list;
    p->inf = y;
    if (r == t) {                  // вставляем после хвоста
        p->next = NULL;
        p->prev = r;
        r->next = p;
        t = p;
    } 
    else {                       // вставляем в середину
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }
}

int main() {
    int n; cout << "Введите количество элементов: "; cin >> n;
    list *head = NULL;
    list *tail = NULL;

    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        push(head, tail, x);
    }
    cout << "Исходный список: ";
    print(head);

    int first = head->inf;         // первый элемент списка
    int maxVal = findMax(head);    // максимальный элемент списка

    cout << "Первый элемент: " << first << endl;
    cout << "Максимальный элемент: " << maxVal << endl;

    // Проходим по списку и вставляем maxVal после каждого узла, равного first
    list *p = head;
    while (p != NULL) {
        if (p->inf == first) {
            // Запоминаем следующий узел ДО вставки,
            // чтобы не зациклиться на только что вставленном
            list *nextNode = p->next;
            insertAfter(head, tail, p, maxVal);
            p = nextNode;          // переходим к узлу, который был следующим
        } 
        else {
            p = p->next;
        }
    }
    cout << "Результат:        ";
    print(head);

    return 0;
}   