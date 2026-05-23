#include <iostream>
using namespace std;

enum Color { RED, BLACK };
struct tree {
    int inf;
    Color color;
    tree *left;
    tree *right;
    tree *parent;
};

tree *grandparent(tree *x) {
    if (x && x->parent) {return x->parent->parent;}
    return NULL;
}

tree *uncle(tree *x) {
    tree *g = grandparent(x);
    if (!g) {return NULL;}
    if (x->parent == g->left) {return g->right;}
    else {return g->left;}
}

tree *sibling(tree *x) {
    if (x && x->parent) {
        if (x == x->parent->left) {
            return x->parent->right;
        }
        else {
            return x->parent->left;
        }
    }
    return NULL;
}

tree *node(tree *p, int x) {
    tree *n = new tree;
    n->inf = x;
    n->color = RED;
    n->left = NULL;
    n->right = NULL;
    n->parent = p;
    return n;
}

tree *root(int x) {
    tree *n = new tree;
    n->inf = x;
    n->color = BLACK;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void rotate_left(tree *(&tr), tree *x) {
    tree *y = x->right;
    x->right = y->left;
    if (y->left) {y->left->parent = x;}
    y->parent = x->parent;
    if (!x->parent) {
        tr = y;
    } 
    else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    if (!y->parent) {y->color = BLACK;}
}

void rotate_right(tree *(&tr), tree *x) {
    tree *y = x->left;
    x->left = y->right;
    if (y->right) {y->right->parent = x;}
    y->parent = x->parent;
    if (!x->parent) {
        tr = y;
    } 
    else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    else {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
    if (!y->parent) {y->color = BLACK;}
}

void insert_case1(tree *(&tr), tree *x);
void insert_case2(tree *(&tr), tree *x);
void insert_case3(tree *(&tr), tree *x);
void insert_case4(tree *(&tr), tree *x);
void insert_case5(tree *(&tr), tree *x);

void insert_case1(tree *(&tr), tree *x) {
    if (!x->parent) {x->color = BLACK;}
    else {insert_case2(tr, x);}
}

void insert_case2(tree *(&tr), tree *x) {
    if (x->parent->color == RED) {insert_case3(tr, x);}
}

void insert_case3(tree *(&tr), tree *x) {
    tree *u = uncle(x);
    tree *g = grandparent(x);
    if (u && u->color == RED && x->parent->color == RED) {
        x->parent->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        insert_case1(tr, g);
    } 
    else {
        insert_case4(tr, x);
    }
}

void insert_case4(tree *(&tr), tree *x) {
    tree *g = grandparent(x);
    if (x == x->parent->right && x->parent == g->left) {
        rotate_left(tr, x->parent);
        x = x->left;
    } 
    else if (x == x->parent->left && x->parent == g->right) {
        rotate_right(tr, x->parent);
        x = x->right;
    }
    insert_case5(tr, x);
}

void insert_case5(tree *(&tr), tree *x) {
    tree *g = grandparent(x);
    x->parent->color = BLACK;
    g->color = RED;
    if (x == x->parent->left && x->parent == g->left) {rotate_right(tr, g);}
    else {rotate_left(tr, g);}
}

void insert(tree *(&tr), tree *prev, int x) {
    if (x < prev->inf) {
        if (!prev->left) {
            prev->left = node(prev, x);
            insert_case1(tr, prev->left);
        } 
        else {
            insert(tr, prev->left, x);
        }
    } 
    else if (x > prev->inf) {
        if (!prev->right) {
            prev->right = node(prev, x);
            insert_case1(tr, prev->right);
        } 
        else {
            insert(tr, prev->right, x);
        }
    }
}

void delete_case1(tree *(&tr), tree *x);
void delete_case2(tree *(&tr), tree *x);
void delete_case3(tree *(&tr), tree *x);
void delete_case4(tree *(&tr), tree *x);
void delete_case5(tree *(&tr), tree *x);
void delete_case6(tree *(&tr), tree *x);

void delete_case1(tree *(&tr), tree *x) {
    if (!x->parent) {
        if (x->left) {tr = x->left;}
        else {tr = x->right;}
    } 
    else {
        delete_case2(tr, x);
    }
}

void delete_case2(tree *(&tr), tree *x) {
    tree *s = sibling(x);
    if (s && s->color == RED) {
        x->parent->color = RED;
        s->color = BLACK;
        if (x == x->parent->left) {rotate_left(tr, x->parent);}
        else {rotate_right(tr, x->parent);}
    }
    delete_case3(tr, x);
}

void delete_case3(tree *(&tr), tree *x) {
    tree *s = sibling(x);
    bool sl_black = (!s->left  || s->left->color  == BLACK);
    bool sr_black = (!s->right || s->right->color == BLACK);
    if (x->parent->color == BLACK && s->color == BLACK && sl_black && sr_black) {
        s->color = RED;
        delete_case1(tr, x->parent);
    } 
    else {
        delete_case4(tr, x);
    }
}

void delete_case4(tree *(&tr), tree *x) {
    tree *s = sibling(x);
    bool sl_black = (!s->left  || s->left->color  == BLACK);
    bool sr_black = (!s->right || s->right->color == BLACK);
    if (x->parent->color == RED && s->color == BLACK && sl_black && sr_black) {
        s->color = RED;
        x->parent->color = BLACK;
    } 
    else {
        delete_case5(tr, x);
    }
}

void delete_case5(tree *(&tr), tree *x) {
    tree *s = sibling(x);
    if (s->color == BLACK) {
        bool sl_red = (s->left  && s->left->color  == RED);
        bool sr_red = (s->right && s->right->color == RED);
        if (x == x->parent->left && sl_red && (!s->right || s->right->color == BLACK)) {
            s->color = RED;
            s->left->color = BLACK;
            rotate_right(tr, s);
        } 
        else if (x == x->parent->right && sr_red && (!s->left || s->left->color == BLACK)) {
            s->color = RED;
            s->right->color = BLACK;
            rotate_left(tr, s);
        }
    }
    delete_case6(tr, x);
}

void delete_case6(tree *(&tr), tree *x) {
    tree *s = sibling(x);
    s->color = x->parent->color;
    x->parent->color = BLACK;
    if (x == x->parent->left) {
        if (s->right) s->right->color = BLACK;
        rotate_left(tr, x->parent);
    } 
    else {
        if (s->left) s->left->color = BLACK;
        rotate_right(tr, x->parent);
    }
}

void replace(tree *(&tr), tree *x) {
    tree *ch;
    if (x->left) {ch = x->left;}
    else {ch = x->right;}
    if (ch) {ch->parent = x->parent;}

    if (!x->parent) {
        tr = ch;
    } 
    else if (x == x->parent->left) {
        x->parent->left = ch;
    } 
    else {
        x->parent->right = ch;
    }
}

tree *find_node(tree *tr, int x) {
    if (!tr || tr->inf == x) {return tr;}
    if (x < tr->inf) {return find_node(tr->left, x);}
    else {return find_node(tr->right, x);}
}

tree *find_max(tree *tr) {
    while (tr->right) {
        tr = tr->right;
    }
    return tr;
}

tree *find_min(tree *tr) {
    while (tr->left) {
        tr = tr->left;
    }
    return tr;
}

void delete_node(tree *(&tr), int val) {
    tree *x = find_node(tr, val);
    if (!x) {cout << "Элемент не найден\n"; return;}

    if (x->left && x->right) {
        tree *buf;
        if (x->inf <= tr->inf) {buf = find_max(x->left);}
        else {buf = find_min(x->right);}
        x->inf = buf->inf;
        x = buf;
    }

    if (x->left || x->right) {
        tree *ch;
        if (x->left) {ch = x->left;}
        else {ch = x->right;}
        replace(tr, x);
        if (x->color == BLACK) {
            if (ch->color == RED) {ch->color = BLACK;}
            else {delete_case1(tr, x);}  
        }
        delete x;
    } 
    else {
        if (x->color == BLACK) {delete_case1(tr, x);}
        if (x->parent) {
            if (x == x->parent->left) {x->parent->left = NULL;}
            else {x->parent->right = NULL;}
        } 
        else {tr = NULL;}
        delete x;
    }
}

void inorder(tree *tr) {  // симметричный обход
    if (tr) {
        inorder(tr->left);
        cout << tr->inf << "(" << (tr->color == RED ? "R" : "B") << ") ";
        inorder(tr->right);
    }
}

int sum_leaves(tree *tr) {
    if (!tr) {return 0;}
    if (!tr->left && !tr->right) {return tr->inf;}
    return sum_leaves(tr->left) + sum_leaves(tr->right);
}

int main() {
    int n, x;
    cout << "Количество элементов: "; cin >> n;

    tree *tr = NULL;
    cout << "Введите элементы:\n";
    for (int i = 0; i < n; ++i) {
        cin >> x;
        if (!tr) {tr = root(x);}
        else {insert(tr, tr, x);}
    }

    cout << "\nСимметричный обход (значение(цвет)):\n";
    inorder(tr);
    cout << "\n";
    cout << "Сумма листьев: " << sum_leaves(tr) << "\n";
    cout << "\nВведите элемент для удаления: "; cin >> x;
    delete_node(tr, x);

    cout << "\nПосле удаления:\n";
    inorder(tr);
    cout << "\n";
    cout << "Сумма листьев: " << sum_leaves(tr) << "\n";

    return 0;
}