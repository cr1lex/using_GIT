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

// удаление узла r
void delNode(list *&h, list *&t, list *r) {
    if (r == h && r == t) {        // единственный элемент
        h = t = NULL;
    } 
    else if (r == h) {           // удаляем голову
        h = h->next;
        h->prev = NULL;
    } 
    else if (r == t) {           // удаляем хвост
        t = t->prev;
        t->next = NULL;
    } 
    else {                       // удаляем из середины
        r->prev->next = r->next;
        r->next->prev = r->prev;
    }
    delete r;
}

// Удаление дубликатов, т.е. оставляем только первые вхождения
void removeDuplicates(list *&h, list *&t) {
    list *p = h;                   // внешний указатель: перебираем "эталоны"
    while (p != NULL) {
        list *q = p->next;         // внутренний указатель: ищем дубликаты после p
        while (q != NULL) {
            list *nextQ = q->next; // запоминаем следующий ДО возможного удаления
            if (q->inf == p->inf)
                delNode(h, t, q);  // нашли дубликат — удаляем
            q = nextQ;
        }
        p = p->next;
    }
}

int main() {
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    list *head = NULL, *tail = NULL;

    cout << "Введите элементы: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        push(head, tail, x);
    }

    cout << "Исходный список: ";
    print(head);

    removeDuplicates(head, tail);

    cout << "Результат:        ";
    print(head);

    return 0;
}