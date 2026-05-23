#include <iostream>
using namespace std;

struct tree {
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree* node(int x) {
    tree *n = new tree;
    n->inf = x;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void insert(tree *(&tr), int x) {
    tree *n = node(x);
    if (!tr) {
        tr = n;
        return;
    }
    tree *y = tr;
    while (y) {
        if (n->inf > y->inf) {
            if (y->right) {
                y = y->right;
            }
            else {
                n->parent = y;
                y->right = n;
                break;
            }
        } 
        else if (n->inf < y->inf) {
            if (y->left) {
                y = y->left;
            } 
            else {
                n->parent = y;
                y->left = n;
                break;
            }
        } 
        else {
            delete n;
            break;
        }
    }
}

tree* find(tree *tr, int x) {
    if (!tr || x == tr->inf) {
        return tr;
    }
    if (x < tr->inf) {
        return find(tr->left, x);
    }
    else {
        return find(tr->right, x);
    }
}

int sumAncestors(tree *n) {
    int sum = 0;
    tree *cur = n->parent;
    while (cur) {
        sum += cur->inf;
        cur = cur->parent;
    }
    return sum;
}

int main() {
    int n, x, val;
    cout << "n = "; cin >> n;
    tree *tr = NULL;
    for (int i = 0; i < n; i++) {
        cout << i << ": "; cin >> x;
        insert(tr, x);
    }
    cout << "X = "; cin >> val;

    tree *found = find(tr, val);
    if (!found) {
        cout << "Узел " << val << " не найден в дереве." << endl;
    } 
    else if (!found->parent) {
        cout << "Узел " << val << " является корнем, предков нет." << endl;
    } 
    else {
        cout << "Сумма предков узла " << val << " = " << sumAncestors(found) << endl;
    }

    return 0;
}